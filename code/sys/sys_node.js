var LibrarySys = {
	$SYS__deps: ['$Browser', '$SYSC'],
	$SYS: {
		timeBase: null,
		DoXHR: function (url, opts) {
			if (!url) {
				return opts.onload(new Error('Must provide a URL'));
			}

			var http = require('http');

			http.get(url, function (res) {
				var buf = [];

				res.on('data', function (data) {
					buf.push(data);
				});

				res.on('end', function () {
					var err = null;
					var data;

					if (!(res.statusCode >= 200 && res.statusCode < 300)) {
						err = new Error('Couldn\'t load ' + url + '. Status: ' + res.statusCode);
					} else {
						var buffer = Buffer.concat(buf);

						// Manually parse out a request expecting a JSON response.
						if (opts.dataType === 'json') {
							var str = buffer.toString();
							try {
								data = JSON.parse(str);
							} catch (e) {
								err = e;
							}
						} else {
							// Convert from node Buffer -> ArrayBuffer.
							data = (new Uint8Array(buffer)).buffer;
						}
					}

					if (opts.onload) {
						opts.onload(err, data);
					}
				});
			});
		},
		LoadingDescription: function (desc) {
			if (desc) {
				console.log(desc);
			}
		},
		LoadingProgress: function (frac) {
			console.log('loaded ' + (frac*100).toFixed(2) + '%');
		},
		PromptEULA: function (callback) {
			var readline = require('readline');
			var lines = SYSC.eula.split('\n');

			console.log('In order to continue, the official Quake3 demo will need to be installed.');
			console.log('Please read through the demo\'s EULA and type \'y\' if you agree to it and would like to continue.\n');

			console.log(lines.pop());

			var rl = readline.createInterface(process.stdin, process.stdout);
			rl.prompt();

			rl.on('line', function (line) {
				line = line.trim();

				if (lines.length) {
					console.log(lines.pop());
					return;
				}

				if (!line) {
					rl.setPrompt('Agree? (y/n): ');
					rl.prompt();
					return;
				}

				rl.close();

				if (line !== 'y' && line !== 'yes') {
					return callback(new Error('You must agree to the EULA to continue'));
				}

				return callback();
			});
		}
	},
	Sys_PlatformInit: function () {
		_CON_SetIsTTY(process.stdin.isTTY);
	},
	Sys_PlatformExit: function () {
	},
	Sys_FS_Startup__deps: ['$Browser', '$FS', '$PATH', '$SYSC'],
	Sys_FS_Startup: function (context) {
		// mount a persistable fs into base if not already mounted
		var name = allocate(intArrayFromString('fs_homepath'), 'i8', ALLOC_STACK);
		var fs_homepath = Pointer_stringify(_Cvar_VariableString(name));
		var localPath = PATH.join('.', fs_homepath);

		// make sure the local path exists
		var mkdirp = function (p) {
			try {
				fs.mkdirSync(p);
			} catch (e) {
				// make the subdirectory and then retry
				if (e.code === 'ENOENT') {
					mkdirp(PATH.dirname(p));
					mkdirp(p);
					return;
				}

				// if we got any other error, let's see if the directory already exists
				var stat;
				try {
					stat = fs.statSync(p);
				}
				catch (e) {
					SYSC.Error('fatal', e.message);
					return;
				}

				if (!stat.isDirectory()) {
					SYSC.Error('fatal', e.message);
				}
			}
		};
		mkdirp(localPath);

		// mount up the local filesystem in emscripten
		var dir;
		try {
			dir = FS.mkdir(fs_homepath, 0777);
		} catch (e) {
			if (!(e instanceof FS.ErrnoError) || e.errno !== ERRNO_CODES.EEXIST) {
				SYSC.Error('fatal', e.message);
			}
		}

		try {
			FS.mount(NODEFS, { root: localPath }, fs_homepath);
		} catch (e) {
			if (!(e instanceof FS.ErrnoError) || e.errno !== ERRNO_CODES.EBUSY) {
				SYSC.Error('fatal', e.message);
			}
		}

		SYSC.FS_Startup(Browser.safeCallback(function (err) {
			if (err) {
				// FIXME cb_free_context(context)
				SYSC.Error('fatal', err);
				return;
			}

			SYSC.ProxyCallback(context);
		}));
	},
	Sys_FS_Shutdown__deps: ['$Browser', '$SYSC'],
	Sys_FS_Shutdown: function (context) {
		var name = allocate(intArrayFromString('fs_homepath'), 'i8', ALLOC_STACK);
		var fs_homepath = Pointer_stringify(_Cvar_VariableString(name));

		SYSC.FS_Shutdown(Browser.safeCallback(function (err) {
			if (err) {
				// FIXME cb_free_context(context)
				SYSC.Error('fatal', err);
				return;
			}

			SYSC.ProxyCallback(context);
		}));
	},
	Sys_Milliseconds: function () {
		var time = process.hrtime();

		if (!SYS.timeBase) {
			SYS.timeBase = time[0] * 1000 + parseInt(time[1] / 1000000, 10);
		}

		return (time[0] * 1000 + parseInt(time[1] / 1000000, 10)) - SYS.timeBase;
	},
	Sys_GetCurrentUser: function () {
		var stack = Runtime.stackSave();
		var ret = allocate(intArrayFromString('player'), 'i8', ALLOC_STACK);
		Runtime.stackRestore(stack);
		return ret;
	},
	Sys_Dialog: function (type, message, title) {
		SYSC.Error('SYS_Dialog not implemented');
	},
	Sys_ErrorDialog: function (error) {
		error = Pointer_stringify(error);
		console.error(error);
		process.exit();
	}
};

autoAddDeps(LibrarySys, '$SYS');
mergeInto(LibraryManager.library, LibrarySys);
