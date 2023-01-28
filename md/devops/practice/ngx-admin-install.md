# ngx-admin安装

[[toc]]

## 参考资料

* [源码地址](https://github.com/akveo/ngx-admin)
* [Docker + Jenkins 部署完整node项目](https://segmentfault.com/a/1190000021462867?utm_source=tag-newest)


## Docker安装Jenkins详细过程

## 安装环境 

* CentOS 7.5
* Docker version 1.13.1

```
1.cmd.exe 用管理员用户打开
2. 切到 D:\CODE\studyPrj\ngx-admin 路径下
3. npm install   会遇到python2等问题  转而使用 cnpm install
4. npm start
```



## 问题记录

1.npm install 报 checking for Python executable "python2" in the PATH
```
转用cnpm 来代替npm
安装cnpm
npm install cnpm -g --registry=https://registry.npm.taobao.org

```

```
Microsoft Windows [版本 10.0.19042.985]
(c) Microsoft Corporation。保留所有权利。

C:\WINDOWS\system32>d:

D:\>cd D:\CODE\studyPrj\ngx-admin

D:\CODE\studyPrj\ngx-admin>npm install

> husky@0.13.3 install D:\CODE\studyPrj\ngx-admin\node_modules\husky
> node ./bin/install.js

husky
setting up hooks
done


> node-sass@4.12.0 install D:\CODE\studyPrj\ngx-admin\node_modules\node-sass
> node scripts/install.js

Downloading binary from https://npm.taobao.org/mirrors/node-sass/v4.12.0/win32-x64-83_binding.node
Cannot download "https://npm.taobao.org/mirrors/node-sass/v4.12.0/win32-x64-83_binding.node":

HTTP error 404 Not Found

Hint: If github.com is not accessible in your location
      try setting a proxy via HTTP_PROXY, e.g.

      export HTTP_PROXY=http://example.com:1234

or configure npm proxy via

      npm config set proxy http://example.com:8080

> core-js@3.6.5 postinstall D:\CODE\studyPrj\ngx-admin\node_modules\@angular-devkit\build-angular\node_modules\core-js
> node -e "try{require('./postinstall')}catch(e){}"

Thank you for using core-js ( https://github.com/zloirock/core-js ) for polyfilling JavaScript standard library!

The project needs your help! Please consider supporting of core-js on Open Collective or Patreon:
> https://opencollective.com/core-js
> https://www.patreon.com/zloirock

Also, the author of core-js ( https://github.com/zloirock ) is looking for a good job -)


> @angular/cli@11.0.7 postinstall D:\CODE\studyPrj\ngx-admin\node_modules\@angular\cli
> node ./bin/postinstall/script.js


> node-sass@4.12.0 postinstall D:\CODE\studyPrj\ngx-admin\node_modules\node-sass
> node scripts/build.js

Building: D:\software\nodejs\node.exe D:\CODE\studyPrj\ngx-admin\node_modules\node-gyp\bin\node-gyp.js rebuild --verbose --libsass_ext= --libsass_cflags= --libsass_ldflags= --libsass_library=
gyp info it worked if it ends with ok
gyp verb cli [
gyp verb cli   'D:\\software\\nodejs\\node.exe',
gyp verb cli   'D:\\CODE\\studyPrj\\ngx-admin\\node_modules\\node-gyp\\bin\\node-gyp.js',
gyp verb cli   'rebuild',
gyp verb cli   '--verbose',
gyp verb cli   '--libsass_ext=',
gyp verb cli   '--libsass_cflags=',
gyp verb cli   '--libsass_ldflags=',
gyp verb cli   '--libsass_library='
gyp verb cli ]
gyp info using node-gyp@3.8.0
gyp info using node@14.15.0 | win32 | x64
gyp verb command rebuild []
gyp verb command clean []
gyp verb clean removing "build" directory
gyp verb command configure []
gyp verb check python checking for Python executable "python2" in the PATH
gyp verb `which` failed Error: not found: python2
gyp verb `which` failed     at getNotFoundError (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:13:12)
gyp verb `which` failed     at F (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:68:19)
gyp verb `which` failed     at E (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:80:29)
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:89:16
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\index.js:42:5
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\windows.js:36:5
gyp verb `which` failed     at FSReqCallback.oncomplete (fs.js:183:21)
gyp verb `which` failed  python2 Error: not found: python2
gyp verb `which` failed     at getNotFoundError (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:13:12)
gyp verb `which` failed     at F (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:68:19)
gyp verb `which` failed     at E (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:80:29)
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:89:16
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\index.js:42:5
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\windows.js:36:5
gyp verb `which` failed     at FSReqCallback.oncomplete (fs.js:183:21) {
gyp verb `which` failed   code: 'ENOENT'
gyp verb `which` failed }
gyp verb check python checking for Python executable "python" in the PATH
gyp verb `which` succeeded python D:\Python3.5\python.EXE
gyp ERR! configure error
gyp ERR! stack Error: Command failed: D:\Python3.5\python.EXE -c import sys; print "%s.%s.%s" % sys.version_info[:3];
gyp ERR! stack   File "<string>", line 1
gyp ERR! stack     import sys; print "%s.%s.%s" % sys.version_info[:3];
gyp ERR! stack                                ^
gyp ERR! stack SyntaxError: invalid syntax
gyp ERR! stack
gyp ERR! stack     at ChildProcess.exithandler (child_process.js:308:12)
gyp ERR! stack     at ChildProcess.emit (events.js:315:20)
gyp ERR! stack     at maybeClose (internal/child_process.js:1048:16)
gyp ERR! stack     at Process.ChildProcess._handle.onexit (internal/child_process.js:288:5)
gyp ERR! System Windows_NT 10.0.19042
gyp ERR! command "D:\\software\\nodejs\\node.exe" "D:\\CODE\\studyPrj\\ngx-admin\\node_modules\\node-gyp\\bin\\node-gyp.js" "rebuild" "--verbose" "--libsass_ext=" "--libsass_cflags=" "--libsass_ldflags=" "--libsass_library="
gyp ERR! cwd D:\CODE\studyPrj\ngx-admin\node_modules\node-sass
gyp ERR! node -v v14.15.0
gyp ERR! node-gyp -v v3.8.0
gyp ERR! not ok
Build failed with error code: 1
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\@angular\compiler-cli\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.13 (node_modules\webpack-dev-server\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.13: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\watchpack\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.13 (node_modules\watchpack-chokidar2\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.13: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\sass\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.1.3 (node_modules\rollup\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.1.3: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.4 (node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.4: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\karma\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})

npm ERR! code ELIFECYCLE
npm ERR! errno 1
npm ERR! node-sass@4.12.0 postinstall: `node scripts/build.js`
npm ERR! Exit status 1
npm ERR!
npm ERR! Failed at the node-sass@4.12.0 postinstall script.
npm ERR! This is probably not a problem with npm. There is likely additional logging output above.

npm ERR! A complete log of this run can be found in:
npm ERR!     D:\software\nodejs\node_cache\_logs\2021-05-28T11_51_50_496Z-debug.log

D:\CODE\studyPrj\ngx-admin>npm install

> node-sass@4.12.0 install D:\CODE\studyPrj\ngx-admin\node_modules\node-sass
> node scripts/install.js

Downloading binary from https://npm.taobao.org/mirrors/node-sass/v4.12.0/win32-x64-83_binding.node
Cannot download "https://npm.taobao.org/mirrors/node-sass/v4.12.0/win32-x64-83_binding.node":

HTTP error 404 Not Found

Hint: If github.com is not accessible in your location
      try setting a proxy via HTTP_PROXY, e.g.

      export HTTP_PROXY=http://example.com:1234

or configure npm proxy via

      npm config set proxy http://example.com:8080

> node-sass@4.12.0 postinstall D:\CODE\studyPrj\ngx-admin\node_modules\node-sass
> node scripts/build.js

Building: D:\software\nodejs\node.exe D:\CODE\studyPrj\ngx-admin\node_modules\node-gyp\bin\node-gyp.js rebuild --verbose --libsass_ext= --libsass_cflags= --libsass_ldflags= --libsass_library=
gyp info it worked if it ends with ok
gyp verb cli [
gyp verb cli   'D:\\software\\nodejs\\node.exe',
gyp verb cli   'D:\\CODE\\studyPrj\\ngx-admin\\node_modules\\node-gyp\\bin\\node-gyp.js',
gyp verb cli   'rebuild',
gyp verb cli   '--verbose',
gyp verb cli   '--libsass_ext=',
gyp verb cli   '--libsass_cflags=',
gyp verb cli   '--libsass_ldflags=',
gyp verb cli   '--libsass_library='
gyp verb cli ]
gyp info using node-gyp@3.8.0
gyp info using node@14.15.0 | win32 | x64
gyp verb command rebuild []
gyp verb command clean []
gyp verb clean removing "build" directory
gyp verb command configure []
gyp verb check python checking for Python executable "python2" in the PATH
gyp verb `which` failed Error: not found: python2
gyp verb `which` failed     at getNotFoundError (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:13:12)
gyp verb `which` failed     at F (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:68:19)
gyp verb `which` failed     at E (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:80:29)
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:89:16
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\index.js:42:5
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\windows.js:36:5
gyp verb `which` failed     at FSReqCallback.oncomplete (fs.js:183:21)
gyp verb `which` failed  python2 Error: not found: python2
gyp verb `which` failed     at getNotFoundError (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:13:12)
gyp verb `which` failed     at F (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:68:19)
gyp verb `which` failed     at E (D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:80:29)
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\which\which.js:89:16
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\index.js:42:5
gyp verb `which` failed     at D:\CODE\studyPrj\ngx-admin\node_modules\isexe\windows.js:36:5
gyp verb `which` failed     at FSReqCallback.oncomplete (fs.js:183:21) {
gyp verb `which` failed   code: 'ENOENT'
gyp verb `which` failed }
gyp verb check python checking for Python executable "python" in the PATH
gyp verb `which` succeeded python D:\Python3.5\python.EXE
gyp ERR! configure error
gyp ERR! stack Error: Command failed: D:\Python3.5\python.EXE -c import sys; print "%s.%s.%s" % sys.version_info[:3];
gyp ERR! stack   File "<string>", line 1
gyp ERR! stack     import sys; print "%s.%s.%s" % sys.version_info[:3];
gyp ERR! stack                                ^
gyp ERR! stack SyntaxError: invalid syntax
gyp ERR! stack
gyp ERR! stack     at ChildProcess.exithandler (child_process.js:308:12)
gyp ERR! stack     at ChildProcess.emit (events.js:315:20)
gyp ERR! stack     at maybeClose (internal/child_process.js:1048:16)
gyp ERR! stack     at Process.ChildProcess._handle.onexit (internal/child_process.js:288:5)
gyp ERR! System Windows_NT 10.0.19042
gyp ERR! command "D:\\software\\nodejs\\node.exe" "D:\\CODE\\studyPrj\\ngx-admin\\node_modules\\node-gyp\\bin\\node-gyp.js" "rebuild" "--verbose" "--libsass_ext=" "--libsass_cflags=" "--libsass_ldflags=" "--libsass_library="
gyp ERR! cwd D:\CODE\studyPrj\ngx-admin\node_modules\node-sass
gyp ERR! node -v v14.15.0
gyp ERR! node-gyp -v v3.8.0
gyp ERR! not ok
Build failed with error code: 1
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/animations@~9.1.1 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/cdk@^9.2.0 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/core@~9.1.1 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/common@~9.1.1 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/forms@~9.1.1 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/platform-browser@~9.1.1 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of @angular/platform-browser-dynamic@~9.1.1 but none is installed. You must install peer dependencies yourself.
npm WARN @swimlane/ngx-charts@14.0.0 requires a peer of tslib@^1.10.0 but none is installed. You must install peer dependencies yourself.
npm WARN bootstrap@4.3.1 requires a peer of jquery@1.9.1 - 3 but none is installed. You must install peer dependencies yourself.
npm WARN bootstrap@4.3.1 requires a peer of popper.js@^1.14.7 but none is installed. You must install peer dependencies yourself.
npm WARN codelyzer@6.0.0 requires a peer of @angular/compiler@>=2.3.1 <11.0.0 || >9.0.0-beta <11.0.0 || >9.1.0-beta <11.0.0 || >9.2.0-beta <11.0.0 but none is installed. You must install peer dependencies yourself.
npm WARN codelyzer@6.0.0 requires a peer of @angular/core@>=2.3.1 <11.0.0 || >9.0.0-beta <11.0.0 || >9.1.0-beta <11.0.0 || >9.2.0-beta <11.0.0 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-ckeditor@1.2.9 requires a peer of @angular/core@^10.0.4 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-ckeditor@1.2.9 requires a peer of @angular/forms@^10.0.4 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-ckeditor@1.2.9 requires a peer of @angular/common@^10.0.4 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-smart-table@1.6.0 requires a peer of @angular/common@^9.0.0 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-smart-table@1.6.0 requires a peer of @angular/core@^9.0.0 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-smart-table@1.6.0 requires a peer of @angular/forms@^9.0.0 but none is installed. You must install peer dependencies yourself.
npm WARN ng2-smart-table@1.6.0 requires a peer of tslib@^1.9.0 but none is installed. You must install peer dependencies yourself.
npm WARN tslint-language-service@0.9.9 requires a peer of typescript@>= 2.3.1 < 3 but none is installed. You must install peer dependencies yourself.
npm WARN tslint-language-service@0.9.9 requires a peer of tslint@>= 4 < 6 but none is installed. You must install peer dependencies yourself.
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\@angular\compiler-cli\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.13 (node_modules\webpack-dev-server\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.13: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\watchpack\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.13 (node_modules\watchpack-chokidar2\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.13: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\sass\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.1.3 (node_modules\rollup\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.1.3: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.4 (node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.4: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@2.3.1 (node_modules\karma\node_modules\fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@2.3.1: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})

npm ERR! code ELIFECYCLE
npm ERR! errno 1
npm ERR! node-sass@4.12.0 postinstall: `node scripts/build.js`
npm ERR! Exit status 1
npm ERR!
npm ERR! Failed at the node-sass@4.12.0 postinstall script.
npm ERR! This is probably not a problem with npm. There is likely additional logging output above.

npm ERR! A complete log of this run can be found in:
npm ERR!     D:\software\nodejs\node_cache\_logs\2021-05-28T12_31_40_017Z-debug.log

√ Installed 76 packages
√ Linked 174 latest versions
[1/2] scripts.install node-sass@^4.12.0 run "node scripts/install.js", root: "D:\\CODE\\studyPrj\\ngx-admin\\node_modules\\_node-sass@4.14.1@node-sass"
Cached binary found at C:\Users\Jason\.npminstall_tarball\node-sass\4.14.1\win32-x64-83_binding.node
[1/2] scripts.install node-sass@^4.12.0 finished in 1s
[1/2] scripts.postinstall node-sass@^4.12.0 run "node scripts/build.js", root: "D:\\CODE\\studyPrj\\ngx-admin\\node_modules\\_node-sass@4.14.1@node-sass"
Binary found at D:\CODE\studyPrj\ngx-admin\node_modules\_node-sass@4.14.1@node-sass\vendor\win32-x64-83\binding.node
Testing binaryrj\ngx-admin>cnpm install
Binary is fine
[1/2] scripts.postinstall node-sass@^4.12.0 finished in 3s
[2/2] scripts.postinstall ngx-admin@7.0.0 run "ngcc --properties es2015 es5 browser module main --first-only --create-ivy-entry-points --tsconfig \"./src/tsconfig.app.json\"", root: "D:\\CODE\\studyPrj\\ngx-admin"
Warning: Entry point 'ngx-echarts/core' contains deep imports into 'D:/CODE/studyPrj/ngx-admin/node_modules/echarts/lib/echarts'. This is probably not a problem, but may cause the compilation of entry points to be out of order.
Compiling @angular/core : es2015 as esm2015
Compiling @angular/cdk/keycodes : es2015 as esm2015
Compiling @angular/compiler/testing : es2015 as esm2015
Compiling @angular/animations : es2015 as esm2015
Compiling @angular/common : es2015 as esm2015
Compiling @angular/cdk/collections : es2015 as esm2015
Compiling @angular/animations/browser : es2015 as esm2015
Compiling @angular/cdk/observers : es2015 as esm2015
Compiling @angular/core/testing : es2015 as esm2015
Compiling @angular/cdk/platform : es2015 as esm2015
Compiling @angular/cdk/bidi : es2015 as esm2015
Compiling @angular/platform-browser : es2015 as esm2015
Compiling @angular/forms : es2015 as esm2015
Compiling @angular/cdk/portal : es2015 as esm2015
Compiling @angular/cdk/scrolling : es2015 as esm2015
Compiling @angular/cdk/a11y : es2015 as esm2015
Compiling @angular/common/http : es2015 as esm2015
Compiling @angular/router : es2015 as esm2015
Compiling @angular/cdk/overlay : es2015 as esm2015
Compiling @angular/cdk/table : es2015 as esm2015
Compiling @angular/platform-browser-dynamic : es2015 as esm2015
Compiling @angular/platform-browser/testing : es2015 as esm2015
Compiling @angular/common/testing : es2015 as esm2015
Compiling @akveo/ng2-completer : es2015 as esm2015
Compiling @angular/animations/browser/testing : es2015 as esm2015
Compiling @nebular/theme : es2015 as esm2015
Compiling @angular/cdk/accordion : es2015 as esm2015
Compiling @angular/cdk/clipboard : es2015 as esm2015
Compiling @angular/cdk/drag-drop : es2015 as esm2015
Compiling @angular/cdk/layout : es2015 as esm2015
Compiling @angular/cdk/stepper : es2015 as esm2015
Compiling @angular/cdk/text-field : es2015 as esm2015
Compiling @angular/cdk/tree : es2015 as esm2015
Compiling @angular/common/http/testing : es2015 as esm2015
Compiling @angular/google-maps : es2015 as esm2015
Compiling @angular/platform-browser/animations : es2015 as esm2015
Compiling @angular/platform-browser-dynamic/testing : es2015 as esm2015
Compiling @angular/router/testing : es2015 as esm2015
Compiling @asymmetrik/ngx-leaflet : module as esm5
Compiling @nebular/security : es2015 as esm2015
Compiling @swimlane/ngx-charts : es2015 as esm2015
Compiling angular2-chartjs : main as commonjs
Compiling ng2-ckeditor : es2015 as esm2015
Compiling @nebular/auth : es2015 as esm2015
Compiling @nebular/eva-icons : es2015 as esm2015
Compiling ng2-smart-table : es2015 as esm2015
Compiling ngx-echarts : es2015 as esm2015
Compiling ngx-echarts/core : es2015 as esm2015
[2/2] scripts.postinstall ngx-admin@7.0.0 finished in 1m
√ Run 2 scripts
deprecate node-sass@4.14.1 › request@^2.88.0 request has been deprecated, see https://github.com/request/request/issues/3142
deprecate node-sass@4.14.1 › request@2.88.2 › har-validator@~5.1.3 this library is no longer supported
Recently updated (since 2021-05-21): 2 packages (detail see file D:\CODE\studyPrj\ngx-admin\node_modules\.recently_updates.txt)
√ All packages installed (190 packages installed from npm registry, used 1m(network 4s), speed 87.29kB/s, json 176(359.25kB), tarball 27.36kB)

D:\CODE\studyPrj\ngx-admin>npm start

> ngx-admin@7.0.0 start D:\CODE\studyPrj\ngx-admin
> ng serve

? Would you like to share anonymous usage data about this project with the Angular Team at
Google under Google’s Privacy Policy at https://policies.google.com/privacy? For more
details and how to change this setting, see http://angular.io/analytics. Yes

Thank you for sharing anonymous usage data. Would you change your mind, the following
command will disable this feature entirely:

    ng analytics project off

    'node-sass' usage is deprecated and will be removed in a future major version. To opt-out of the deprecated behaviour and start using 'sass' uninstall 'node-sass'.
√ Browser application bundle generation complete.

Initial Chunk Files                         | Names                                    |      Size
vendor.js                                   | vendor                                   |   7.46 MB
main.js                                     | main                                     |   1.99 MB
styles.css, styles.js                       | styles                                   |   1.95 MB
scripts.js                                  | scripts                                  |   1.30 MB
polyfills.js                                | polyfills                                | 650.21 kB
runtime.js                                  | runtime                                  |  12.41 kB

                                            | Initial Total                            |  13.35 MB

Lazy Chunk Files                            | Names                                    |      Size
pages-pages-module.js                       | pages-pages-module                       |  21.83 MB
extra-components-extra-components-module.js | extra-components-extra-components-module |   4.27 MB
modal-overlays-modal-overlays-module.js     | modal-overlays-modal-overlays-module     |   2.53 MB
tables-tables-module.js                     | tables-tables-module                     |   1.64 MB
maps-maps-module.css, maps-maps-module.js   | maps-maps-module                         |   1.59 MB
charts-charts-module.js                     | charts-charts-module                     |   1.22 MB
ui-features-ui-features-module.js           | ui-features-ui-features-module           |   1.16 MB
layout-layout-module.js                     | layout-layout-module                     |   1.12 MB
forms-forms-module.js                       | forms-forms-module                       | 776.21 kB
editors-editors-module.js                   | editors-editors-module                   | 586.70 kB

Build at: 2021-05-28T12:44:06.518Z - Hash: e13372ff137339fe31d5 - Time: 141095ms

** Angular Live Development Server is listening on localhost:4200, open your browser on http://localhost:4200/ **


√ Compiled successfully.

```

