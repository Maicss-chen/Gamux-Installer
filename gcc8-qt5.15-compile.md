# 编译参数

配合打包器和安装器的编译参数如下：

```
QMAKE_CXXFLAGS+=-Wno-error QMAKE_FXXLAGS=-no-exceptions ./configure \
	-confirm-license \
	-opensource \
	-release \
	-optimize-size \
	-prefix "/opt/qt5.15" \
	-shared \
	-c++std c++11 \
	-silent \
	-no-compile-examples \
	-nomake tests \
	-nomake examples \
	-qt-doubleconversion \
	-no-glib \
	-no-iconv \
	-qt-pcre \
	-no-zlib \
	-no-ssl \
	-no-openssl \
	-no-libproxy \
	-no-cups \
	-system-freetype \
	-no-gtk \
	-no-opengl \
	-no-vulkan \
	-qpa xcb \
	-no-directfb \
	-no-eglfs \
	-no-gbm \
	-no-kms \
	-no-linuxfb \
	-xcb \
	-xcb-xlib \
	-no-libudev \
	-no-evdev \
	-no-libinput \
	-no-mtdev \
	-no-tslib \
	-no-ico \
	-no-gif \
	-qt-libpng \
	-qt-libjpeg \
	-no-icu \
	-no-feature-sqlmodel \
	-no-harfbuzz \
	-no-feature-texthtmlparser \
	-no-feature-textodfwriter \
	-no-feature-textmarkdownreader -no-feature-textmarkdownwriter \
	-no-feature-sessionmanager \
	-no-sql-mysql \
	-no-sql-odbc \
	-no-sql-tds \
	-no-sql-psql \
	-no-sql-sqlite \
	-no-feature-testlib \
	-no-feature-sql \
	-nomake tools \
	-strip \
	-ltcg \
	-no-pch \
	-fontconfig \
	-feature-relocatable \
	-recheck
```

# 说明

## 编译参数

qt的编译参数可通过<code>./configure --help</code> 查询。

```
Configure understands variable assignments like VAR=value on the command line.
Each uppercased library name (obtainable with -list-libraries) supports the
suffixes _INCDIR, _LIBDIR, _PREFIX (INCDIR=PREFIX/include, LIBDIR=PREFIX/lib),
_LIBS, and - on Windows and Darwin - _LIBS_DEBUG and _LIBS_RELEASE. E.g.,
ICU_PREFIX=/opt/icu42 ICU_LIBS="-licui18n -licuuc -licudata".

It is also possible to manipulate any QMAKE_* variable, to amend the values
from the mkspec for the build of Qt itself, e.g., QMAKE_CXXFLAGS+=-g3.

Note that the *_LIBS* and QMAKE_* assignments manipulate lists, so items
containing meta characters (spaces in particular) need to be quoted according
to qmake rules. On top of that, the assignments as a whole need to be quoted
according to shell rules. It is recommended to use single quotes for the inner
quoting and double quotes for the outer quoting.

Top-level installation directories:
  -prefix <dir> ...... The deployment directory, as seen on the target device.
                       [/usr/local/Qt-$QT_VERSION; qtbase build directory if
                       -developer-build]
  -extprefix <dir> ... The installation directory, as seen on the host machine.
                       [SYSROOT/PREFIX]
  -hostprefix [dir] .. The installation directory for build tools running on
                       the host machine. If [dir] is not given, the current
                       build directory will be used. [EXTPREFIX]
  -external-hostbindir <path> ... Path to Qt tools built for this machine.
                       Use this when -platform does not match the current
                       system, i.e., to make a Canadian Cross Build.

Fine tuning of installation directory layout. Note that all directories
except -sysconfdir should be located under -prefix/-hostprefix:

  -bindir <dir> ......... Executables [PREFIX/bin]
  -headerdir <dir> ...... Header files [PREFIX/include]
  -libdir <dir> ......... Libraries [PREFIX/lib]
  -archdatadir <dir> .... Arch-dependent data [PREFIX]
  -plugindir <dir> ...... Plugins [ARCHDATADIR/plugins]
  -libexecdir <dir> ..... Helper programs [ARCHDATADIR/bin on Windows,
                          ARCHDATADIR/libexec otherwise]
  -importdir <dir> ...... QML1 imports [ARCHDATADIR/imports]
  -qmldir <dir> ......... QML2 imports [ARCHDATADIR/qml]
  -datadir <dir> ........ Arch-independent data [PREFIX]
  -docdir <dir> ......... Documentation [DATADIR/doc]
  -translationdir <dir> . Translations [DATADIR/translations]
  -sysconfdir <dir> ..... Settings used by Qt programs [PREFIX/etc/xdg]
  -examplesdir <dir> .... Examples [PREFIX/examples]
  -testsdir <dir> ....... Tests [PREFIX/tests]

  -hostbindir <dir> ..... Host executables [HOSTPREFIX/bin]
  -hostlibdir <dir> ..... Host libraries [HOSTPREFIX/lib]
  -hostdatadir <dir> .... Data used by qmake [HOSTPREFIX]

Conventions for the remaining options: When an option's description is
followed by a list of values in brackets, the interpretation is as follows:
'yes' represents the bare option; all other values are possible prefixes to
the option, e.g., -no-gui. Alternatively, the value can be assigned, e.g.,
--gui=yes. Values are listed in the order they are tried if not specified;
'auto' is a shorthand for 'yes/no'. Solitary 'yes' and 'no' represent binary
options without auto-detection.

Configure meta:

  -help, -h ............ Display this help screen
  -verbose, -v ......... Print verbose messages during configuration
  -continue ............ Continue configure despite errors
  -redo ................ Re-configure with previously used options.
                         Additional options may be passed, but will not be
                         saved for later use by -redo.
  -recheck [test,...] .. Discard cached negative configure test results.
                         Use this after installing missing dependencies.
                         Alternatively, if tests are specified, only their
                         results are discarded.
  -recheck-all ......... Discard all cached configure test results.

  -feature-<feature> ... Enable <feature>
  -no-feature-<feature>  Disable <feature> [none]
  -list-features ....... List available features. Note that some features
                         have dedicated command line options as well.

  -list-libraries ...... List possible external dependencies.

Build options:

  -opensource .......... Build the Open-Source Edition of Qt
  -commercial .......... Build the Commercial Edition of Qt
  -confirm-license ..... Automatically acknowledge the license

  -release ............. Build Qt with debugging turned off [yes]
  -debug ............... Build Qt with debugging turned on [no]
  -debug-and-release ... Build two versions of Qt, with and without
                         debugging turned on [yes] (Apple and Windows only)
  -optimize-debug ...... Enable debug-friendly optimizations in debug builds
                         [auto] (Not supported with MSVC or Clang toolchains)
  -optimize-size ....... Optimize release builds for size instead of speed [no]
  -optimized-tools ..... Build optimized host tools even in debug build [no]
  -force-debug-info .... Create symbol files for release builds [no]
  -separate-debug-info . Split off debug information to separate files [no]
  -gdb-index ........... Index the debug info to speed up GDB
                         [no; auto if -developer-build with debug info]
  -strip ............... Strip release binaries of unneeded symbols [yes]
  -gc-binaries ......... Place each function or data item into its own section
                         and enable linker garbage collection of unused
                         sections. [auto for static builds, otherwise no]
  -force-asserts ....... Enable Q_ASSERT even in release builds [no]
  -developer-build ..... Compile and link Qt for developing Qt itself
                         (exports for auto-tests, extra checks, etc.) [no]

  -shared .............. Build shared Qt libraries [yes] (no for UIKit)
  -static .............. Build static Qt libraries [no] (yes for UIKit)
  -framework ........... Build Qt framework bundles [yes] (Apple only)

  -platform <target> ... Select host mkspec [detected]
  -xplatform <target> .. Select target mkspec when cross-compiling [PLATFORM]
  -device <name> ....... Cross-compile for device <name>
  -device-option <key=value> ... Add option for the device mkspec

  -appstore-compliant .. Disable code that is not allowed in platform app stores.
                         This is on by default for platforms which require distribution
                         through an app store by default, in particular Android,
                         iOS, tvOS, watchOS, and Universal Windows Platform. [auto]

  -qtnamespace <name> .. Wrap all Qt library code in 'namespace <name> {...}'.
  -qtlibinfix <infix> .. Rename all libQt5*.so to libQt5*<infix>.so.
  -qtlibinfix-plugins .. Rename Qt plugins according to -qtlibinfix [no]

  -testcocoon .......... Instrument with the TestCocoon code coverage tool [no]
  -gcov ................ Instrument with the GCov code coverage tool [no]

  -trace [backend] ..... Enable instrumentation with tracepoints.
                         Currently supported backends are 'etw' (Windows) and
                         'lttng' (Linux), or 'yes' for auto-detection. [no]

  -sanitize {address|thread|memory|fuzzer-no-link|undefined}
                         Instrument with the specified compiler sanitizer.
                         Note that some sanitizers cannot be combined;
                         for example, -sanitize address cannot be combined with
                         -sanitize thread.

  -coverage {trace-pc-guard|source-based}
                         Specify the 'trace-pc-guard' coverage instrumentation for
                         sanitizers or generate instrumented code to collect execution
                         counts and enable code coverage analysis, respectively. (Clang only)

  -c++std <edition> .... Select C++ standard <edition> [c++2a/c++17/c++14/c++11]
                         (Not supported with MSVC 2015)

  -sse2 ................ Use SSE2 instructions [auto]
  -sse3/-ssse3/-sse4.1/-sse4.2/-avx/-avx2/-avx512
                         Enable use of particular x86 instructions [auto]
                         Enabled ones are still subject to runtime detection.
  -mips_dsp/-mips_dspr2  Use MIPS DSP/rev2 instructions [auto]

  -qreal <type> ........ typedef qreal to the specified type. [double]
                         Note: this affects binary compatibility.

  -R <string> .......... Add an explicit runtime library path to the Qt
                         libraries. Supports paths relative to LIBDIR.
  -rpath ............... Link Qt libraries and executables using the library
                         install path as a runtime library path. Similar to
                         -R LIBDIR. On Apple platforms, disabling this implies
                         using absolute install names (based in LIBDIR) for
                         dynamic libraries and frameworks. [auto]

  -reduce-exports ...... Reduce amount of exported symbols [auto]
  -reduce-relocations .. Reduce amount of relocations [auto] (Unix only)

  -plugin-manifests .... Embed manifests into plugins [no] (Windows only)
  -static-runtime ...... With -static, use static runtime [no] (Windows only)

  -pch ................. Use precompiled headers [auto]
  -ltcg ................ Use Link Time Code Generation [no]
  -linker [bfd,gold,lld] Force use of the GNU ld, GNU gold or LLVM/LLD linker
                         instead of default one (GCC only)
  -incredibuild-xge .... Use the IncrediBuild XGE [no] (Windows only)
  -ccache .............. Use the ccache compiler cache [no] (Unix only)
  -make-tool <tool> .... Use <tool> to build qmake [nmake] (Windows only)
  -mp .................. Use multiple processors for compilation (MSVC only)

  -warnings-are-errors . Treat warnings as errors [no; yes if -developer-build]
  -silent .............. Reduce the build output so that warnings and errors
                         can be seen more easily

Build environment:

  -sysroot <dir> ....... Set <dir> as the target sysroot
  -gcc-sysroot ......... With -sysroot, pass --sysroot to the compiler [yes]

  -pkg-config .......... Use pkg-config [auto] (Unix only)

  -D <string> .......... Pass additional preprocessor define
  -I <string> .......... Pass additional include path
  -L <string> .......... Pass additional library path
  -F <string> .......... Pass additional framework path (Apple only)

  -sdk <sdk> ........... Build Qt using Apple provided SDK <sdk>. The argument
                         should be one of the available SDKs as listed by
                         'xcodebuild -showsdks'.
                         Note that the argument applies only to Qt libraries
                         and applications built using the target mkspec - not
                         host tools such as qmake, moc, rcc, etc.

  -android-sdk path .... Set Android SDK root path [$ANDROID_SDK_ROOT]
  -android-ndk path .... Set Android NDK root path [$ANDROID_NDK_ROOT]
  -android-ndk-platform  Set Android platform
  -android-ndk-host .... Set Android NDK host (linux-x86, linux-x86_64, etc.)
                         [$ANDROID_NDK_HOST]
  -android-abis .......  Comma separated Android abis, default is:
                         armeabi-v7a,arm64-v8a,x86,x86_64
  -android-javac-target  Set the javac build target version [7]
  -android-javac-source  Set the javac build source version [7]
  -android-style-assets  Automatically extract style assets from the device at
                         run time. This option makes the Android style behave
                         correctly, but also makes the Android platform plugin
                         incompatible with the LGPL2.1. [yes]

Component selection:

  -skip <repo> ......... Exclude an entire repository from the build.
  -make <part> ......... Add <part> to the list of parts to be built.
                         Specifying this option clears the default list first.
                         [libs and examples, also tools if not cross-building,
                         also tests if -developer-build]
  -nomake <part> ....... Exclude <part> from the list of parts to be built.
  -compile-examples .... When unset, install only the sources of examples
                         [no on WebAssembly, otherwise yes]
  -gui ................. Build the Qt GUI module and dependencies [yes]
  -widgets ............. Build the Qt Widgets module and dependencies [yes]
  -no-dbus ............. Do not build the Qt D-Bus module
                         [default on Android and Windows]
  -dbus-linked ......... Build Qt D-Bus and link to libdbus-1 [auto]
  -dbus-runtime ........ Build Qt D-Bus and dynamically load libdbus-1 [no]
  -accessibility ....... Enable accessibility support [yes]
                         Note: Disabling accessibility is not recommended.

Qt comes with bundled copies of some 3rd party libraries. These are used
by default if auto-detection of the respective system library fails.

Core options:

  -doubleconversion .... Select used double conversion library [system/qt/no]
                         No implies use of sscanf_l and snprintf_l (imprecise).
  -glib ................ Enable Glib support [no; auto on Unix]
  -eventfd ............. Enable eventfd support
  -inotify ............. Enable inotify support
  -iconv ............... Enable iconv(3) support [posix/sun/gnu/no] (Unix only)
  -icu ................. Enable ICU support [auto]
  -pcre ................ Select used libpcre2 [system/qt/no]
  -pps ................. Enable PPS support [auto] (QNX only)
  -zlib ................ Select used zlib [system/qt]

  Logging backends:
    -journald .......... Enable journald support [no] (Unix only)
    -syslog ............ Enable syslog support [no] (Unix only)
    -slog2 ............. Enable slog2 support [auto] (QNX only)

Network options:

  -ssl ................. Enable either SSL support method [auto]
  -no-openssl .......... Do not use OpenSSL [default on Apple and WinRT]
  -openssl-linked ...... Use OpenSSL and link to libssl [no]
  -openssl-runtime ..... Use OpenSSL and dynamically load libssl [auto]
  -schannel ............ Use Secure Channel [no] (Windows only)
  -securetransport ..... Use SecureTransport [auto] (Apple only)

  -sctp ................ Enable SCTP support [no]

  -libproxy ............ Enable use of libproxy [no]
  -system-proxies ...... Use system network proxies by default [yes]

Gui, printing, widget options:

  -cups ................ Enable CUPS support [auto] (Unix only)

  -fontconfig .......... Enable Fontconfig support [auto] (Unix only)
  -freetype ............ Select used FreeType [system/qt/no]
  -harfbuzz ............ Select used HarfBuzz-NG [system/qt/no]
                         (Not auto-detected on Apple and Windows)

  -gtk ................. Enable GTK platform theme support [auto]

  -lgmon ............... Enable lgmon support [auto] (QNX only)

  -no-opengl ........... Disable OpenGL support
  -opengl <api> ........ Enable OpenGL support. Supported APIs:
                         es2 (default on Windows), desktop (default on Unix),
                         dynamic (Windows only)
  -opengles3 ........... Enable OpenGL ES 3.x support instead of ES 2.x [auto]
  -egl ................. Enable EGL support [auto]
  -angle ............... Use bundled ANGLE to support OpenGL ES 2.0 [auto]
                         (Windows only)
  -combined-angle-lib .. Merge LibEGL and LibGLESv2 into LibANGLE (Windows only)

  -qpa <name> .......... Select default QPA backend(s) (e.g., xcb, cocoa, windows)
                         A prioritized list separated by semi-colons.
  -xcb-xlib............. Enable Xcb-Xlib support [auto]

  Platform backends:
    -direct2d .......... Enable Direct2D support [auto] (Windows only)
    -directfb .......... Enable DirectFB support [no] (Unix only)
    -eglfs ............. Enable EGLFS support [auto; no on Android and Windows]
    -gbm ............... Enable backends for GBM [auto] (Linux only)
    -kms ............... Enable backends for KMS [auto] (Linux only)
    -linuxfb ........... Enable Linux Framebuffer support [auto] (Linux only)
    -xcb ............... Enable X11 support [auto] (Linux only)

  Input backends:
    -libudev............ Enable udev support [auto]
    -evdev ............. Enable evdev support [auto]
    -imf ............... Enable IMF support [auto] (QNX only)
    -libinput .......... Enable libinput support [auto]
    -mtdev ............. Enable mtdev support [auto]
    -tslib ............. Enable tslib support [auto]
    -bundled-xcb-xinput  Use bundled XInput2 support [auto]
    -xkbcommon ......... Enable key mapping support [auto]

  Image formats:
    -gif ............... Enable reading support for GIF [auto]
    -ico ............... Enable support for ICO [yes]
    -libpng ............ Select used libpng [system/qt/no]
    -libjpeg ........... Select used libjpeg [system/qt/no]

Database options:

  -sql-<driver> ........ Enable SQL <driver> plugin. Supported drivers:
                         db2 ibase mysql oci odbc psql sqlite2 sqlite tds
                         [all auto]
  -sqlite .............. Select used sqlite3 [system/qt]
```

## 特性

特性的参数可通过<code>./configure --list-features</code>查询，可定制qt组件的颗粒，例如不编译颜色选择框；通过-feature-<feature> 和-no-feature-<feature>启用和禁用特性。

```
abstractbutton .......... Widgets: 按钮部件的抽象基类，提供按钮共有的功能。禁用按钮将不会被编译。
abstractslider .......... Widgets: QScrollBar、QSlider 和 QDial 等小部件的通用超类。禁用后滚动条、进度条和刻度盘部件将不编译。
accessibility ........... Utilities: Provides accessibility support.
action .................. Kernel: Provides widget actions.
animation ............... Utilities: 动画框架
appstore-compliant ...... Disables code that is not allowed in platform app stores
bearermanagement ........ Networking: Provides bearer management for the network stack.
big_codecs .............. Internationalization: 支持大型字符编码，例如CJK（中日韩字符）
binaryjson .............. Utilities: Provides support for the deprecated binary JSON format.
buttongroup ............. Widgets: Supports organizing groups of button widgets.
calendarwidget .......... Widgets: 提供基于月度的日历小部件，用户以选择日期。
cborstreamreader ........ Utilities: 提供对读取 CBOR 二进制格式的支持。
cborstreamwriter ........ Utilities: 提供对编写 CBOR 二进制格式的支持。
checkbox ................ Widgets: 提供带有文本的复选框。
clipboard ............... Kernel: 提供剪切和粘贴操作。
codecs .................. Internationalization: 支持非 unicode 文本转换。
colordialog ............. Dialogs: 提供颜色选择对话框小部件。
colornames .............. Painting: Supports color names such as "red", used by QColor and by some HTML documents.
columnview .............. ItemViews: Provides a model/view implementation of a column view.
combobox ................ Widgets: 提供下拉框式选项列表。
commandlineparser ....... Utilities: 提供对命令行解析的支持。
commandlinkbutton ....... Widgets: Provides a Vista style command link button.
completer ............... Utilities: Provides completions based on an item model.
concatenatetablesproxymodel . ItemViews: Supports concatenating source models.
concurrent .............. Kernel: Provides a high-level multi-threading API.
contextmenu ............. Widgets: Adds pop-up menus on right mouse click to numerous widgets.
cssparser ............... Kernel: CSS解析器。
cups .................... Painting: 提供对通用 Unix 打印系统的支持。
cursor .................. Kernel: 鼠标指针支持。
datawidgetmapper ........ ItemViews: Provides mapping between a section of a data model to widgets.
datestring .............. Data structures: Provides conversion between dates and strings.
datetimeedit ............ Widgets: Supports editing dates and times.
datetimeparser .......... Utilities: Provides support for parsing date-time texts.
desktopservices ......... Utilities: Provides methods for accessing common desktop services.
dial .................... Widgets: Provides a rounded range control, e.g., like a speedometer.
dialog .................. Dialogs: Base class of dialog windows.
dialogbuttonbox ......... Dialogs: Presents buttons in a layout that is appropriate for the current widget style.
dirmodel ................ ItemViews: Provides a data model for the local filesystem.
dnslookup ............... Networking: Provides API for DNS lookups.
dockwidget .............. Widgets: Supports docking widgets inside a QMainWindow or floated as a top-level window on the desktop.
dom ..................... File I/O: Supports the Document Object Model.
draganddrop ............. Kernel: Supports the drag and drop mechansim.
dtls .................... Networking: Provides a DTLS implementation
easingcurve ............. Utilities: Provides easing curve.
effects ................. Kernel: Provides special widget effects (e.g. fading and scrolling).
errormessage ............ Dialogs: 提供错误消息显示对话框。
filedialog .............. Dialogs: 文件选择对话框小部件。
filesystemiterator ...... File I/O: Provides fast file system iteration.
filesystemmodel ......... File I/O: Provides a data model for the local filesystem.
filesystemwatcher ....... File I/O: Provides an interface for monitoring files and directories for modifications.
fontcombobox ............ Widgets: 选择字体系列的组合对话框。
fontdialog .............. Dialogs: 选择字体的小对话框。
formlayout .............. Widgets: Manages forms of input widgets and their associated labels.
freetype ................ Fonts: 支持FreeType2库。
fscompleter ............. Utilities: Provides file name completion in QFileDialog.
ftp ..................... Networking: Provides support for the File Transfer Protocol in QNetworkAccessManager.
future .................. Kernel: Provides QFuture and related classes.
gestures ................ Utilities: Provides a framework for gestures.
graphicseffect .......... Widgets: Provides various graphics effects.
graphicsview ............ Widgets: Provides a canvas/sprite framework.
groupbox ................ Widgets: Provides widget grouping boxes with frames.
gssapi .................. Networking: Enable SPNEGO authentication through GSSAPI
highdpiscaling .......... Kernel: Provides automatic scaling of DPI-unaware applications on high-DPI displays.
hijricalendar ........... Utilities: Generic basis for Islamic calendars, providing shared locale data
http .................... Networking: Provides support for the Hypertext Transfer Protocol in QNetworkAccessManager.
iconv ................... Internationalization: 提供国际化，unix系统上。
identityproxymodel ...... ItemViews: Supports proxying a source model unmodified.
im ...................... Kernel: Provides complex input methods.
image_heuristic_mask .... Images: Supports creating a 1-bpp heuristic mask for images.
image_text .............. Images: Supports image file text strings.
imageformat_bmp ......... Images: Supports Microsoft's Bitmap image file format.
imageformat_jpeg ........ Images: Supports the Joint Photographic Experts Group image file format.
imageformat_png ......... Images: Supports the Portable Network Graphics image file format.
imageformat_ppm ......... Images: Supports the Portable Pixmap image file format.
imageformat_xbm ......... Images: Supports the X11 Bitmap image file format.
imageformat_xpm ......... Images: Supports the X11 Pixmap image file format.
imageformatplugin ....... Images: Provides a base for writing a image format plugins.
inputdialog ............. Dialogs: Provides a simple convenience dialog to get a single value from the user.
islamiccivilcalendar .... Utilities: Support the Islamic Civil calendar
itemmodel ............... ItemViews: Provides the item model for item views
itemmodeltester ......... Provides a utility to test item models.
itemviews ............... ItemViews: Provides the model/view architecture managing the relationship between data and the way it is presented to the user.
jalalicalendar .......... Utilities: Support the Jalali (Persian) calendar
keysequenceedit ......... Widgets: Provides a widget for editing QKeySequences.
label ................... Widgets: Provides a text or image display.
lcdnumber ............... Widgets: Provides LCD-like digits.
library ................. File I/O: Provides a wrapper for dynamically loaded libraries.
lineedit ................ Widgets: Provides single-line edits.
listview ................ ItemViews: Provides a list or icon view onto a model.
listwidget .............. Widgets: Provides item-based list widgets.
localserver ............. Networking: Provides a local socket based server.
mainwindow .............. Widgets: Provides main application windows.
mdiarea ................. Widgets: Provides an area in which MDI windows are displayed.
menu .................... Widgets: Provides popup-menus.
menubar ................. Widgets: Provides pull-down menu items.
messagebox .............. Dialogs: Provides message boxes displaying informative messages and simple questions.
mimetype ................ Utilities: Provides MIME type handling.
movie ................... Images: Supports animated images.
multiprocess ............ Utilities: Provides support for detecting the desktop environment, launching external processes and opening URLs.
netlistmgr .............. Networking: Use Network List Manager to keep track of network connectivity
networkdiskcache ........ Networking: Provides a disk cache for network resources.
networkinterface ........ Networking: Supports enumerating a host's IP addresses and network interfaces.
networkproxy ............ Networking: Provides network proxy support.
ocsp .................... Networking: Provides OCSP stapling support
pdf ..................... Painting: Provides a PDF backend for QPainter.
picture ................. Painting: Supports recording and replaying QPainter commands.
printdialog ............. Dialogs: Provides a dialog widget for specifying printer configuration.
printer ................. Painting: Provides a printer backend of QPainter.
printpreviewdialog ...... Dialogs: Provides a dialog for previewing and configuring page layouts for printer output.
printpreviewwidget ...... Widgets: Provides a widget for previewing page layouts for printer output.
process ................. File I/O: Supports external process invocation.
processenvironment ...... File I/O: Provides a higher-level abstraction of environment variables.
progressbar ............. Widgets: Supports presentation of operation progress.
progressdialog .......... Dialogs: Provides feedback on the progress of a slow operation.
properties .............. Kernel: Supports scripting Qt-based applications.
proxymodel .............. ItemViews: Supports processing of data passed between another model and a view.
pushbutton .............. Widgets: Provides a command button.
radiobutton ............. Widgets: Provides a radio button with a text label.
raster-64bit ............ Painting: Internal painting support for 64 bit (16 bpc) rasterization.
regularexpression ....... Kernel: Provides an API to Perl-compatible regular expressions.
relocatable ............. Enable the Qt installation to be relocated.
resizehandler ........... Widgets: Provides an internal resize handler for dock widgets.
rubberband .............. Widgets: Supports using rubberbands to indicate selections and boundaries.
scrollarea .............. Widgets: Supports scrolling views onto widgets.
scrollbar ............... Widgets: Provides scrollbars allowing the user access parts of a document that is larger than the widget used to display it.
scroller ................ Widgets: Enables kinetic scrolling for any scrolling widget or graphics item.
sessionmanager .......... Kernel: Provides an interface to the windowing system's session management.
settings ................ File I/O: Provides persistent application settings.
sha3-fast ............... Utilities: Optimizes SHA3 for speed instead of size.
sharedmemory ............ Kernel: Provides access to a shared memory segment.
shortcut ................ Kernel: Provides keyboard accelerators and shortcuts.
sizegrip ................ Widgets: Provides corner-grips for resizing top-level windows.
slider .................. Widgets: Provides sliders controlling a bounded value.
socks5 .................. Networking: Provides SOCKS5 support in QNetworkProxy.
sortfilterproxymodel .... ItemViews: Supports sorting and filtering of data passed between another model and a view.
spinbox ................. Widgets: Provides spin boxes handling integers and discrete sets of values.
splashscreen ............ Widgets: Supports splash screens that can be shown during application startup.
splitter ................ Widgets: Provides user controlled splitter widgets.
sqlmodel ................ Provides item model classes backed by SQL databases.
sspi .................... Networking: Enable NTLM/SPNEGO authentication through SSPI
stackedwidget ........... Widgets: Provides stacked widgets.
standarditemmodel ....... ItemViews: Provides a generic model for storing custom data.
statemachine ............ Utilities: Provides hierarchical finite state machines.
statusbar ............... Widgets: Supports presentation of status information.
statustip ............... Widgets: Supports status tip functionality and events.
stringlistmodel ......... ItemViews: Provides a model that supplies strings to views.
style-stylesheet ........ Styles: Provides a widget style which is configurable via CSS.
syntaxhighlighter ....... Widgets: Supports custom syntax highlighting.
systemsemaphore ......... Kernel: Provides a general counting system semaphore.
systemtrayicon .......... Utilities: Provides an icon for an application in the system tray.
tabbar .................. Widgets: Provides tab bars, e.g., for use in tabbed dialogs.
tabletevent ............. Kernel: Supports tablet events.
tableview ............... ItemViews: Provides a default model/view implementation of a table view.
tablewidget ............. Widgets: Provides item-based table views.
tabwidget ............... Widgets: Supports stacking tabbed widgets.
temporaryfile ........... File I/O: Provides an I/O device that operates on temporary files.
testlib_selfcover ....... Gauges how thoroughly testlib's selftest exercises testlib's code
textbrowser ............. Widgets: Supports HTML document browsing.
textcodec ............... Internationalization: Supports conversions between text encodings.
textdate ................ Data structures: Supports month and day names in dates.
textedit ................ Widgets: Supports rich text editing.
texthtmlparser .......... Kernel: Provides a parser for HTML.
textmarkdownreader ...... Kernel: Provides a Markdown (CommonMark and GitHub) reader
textmarkdownwriter ...... Kernel: Provides a Markdown (CommonMark) writer
textodfwriter ........... Kernel: Provides an ODF writer.
thread .................. Kernel: Provides QThread and related classes.
timezone ................ Utilities: Provides support for time-zone handling.
toolbar ................. Widgets: Provides movable panels containing a set of controls.
toolbox ................. Widgets: Provides columns of tabbed widget items.
toolbutton .............. Widgets: Provides quick-access buttons to commands and options.
tooltip ................. Widgets: Supports presentation of tooltips.
topleveldomain .......... Utilities: Provides support for extracting the top level domain from URLs.
translation ............. Internationalization: Supports translations using QObject::tr().
transposeproxymodel ..... ItemViews: Provides a proxy to swap rows and columns of a model.
treeview ................ ItemViews: Provides a default model/view implementation of a tree view.
treewidget .............. Widgets: Provides views using tree models.
tuiotouch ............... Provides the TuioTouch input plugin.
udpsocket ............... Networking: Provides access to UDP sockets.
undocommand ............. Utilities: Applies (redo or) undo of a single change in a document.
undogroup ............... Utilities: Provides the ability to cluster QUndoCommands.
undostack ............... Utilities: Provides the ability to (redo or) undo a list of changes in a document.
undoview ................ Utilities: Provides a widget which shows the contents of an undo stack.
valgrind ................ Profiling support with callgrind.
validator ............... Widgets: Supports validation of input text.
whatsthis ............... Widget Support: Supports displaying "What's this" help.
wheelevent .............. Kernel: Supports wheel events.
widgettextcontrol ....... Widgets: Provides text control functionality to other widgets.
wizard .................. Dialogs: Provides a framework for multi-page click-through dialogs.
xmlstream ............... Kernel: Provides a simple streaming API for XML.
xmlstreamreader ......... Kernel: Provides a well-formed XML parser with a simple streaming API.
xmlstreamwriter ......... Kernel: Provides a XML writer with a simple streaming API.
```

## 依赖查询

查询需要安装的依赖可通过<code>./configure -list-libraries</code>查询。

```
qtbase:
  dbus
  libdl
  libudev
  zlib
  zstd
core:
  advapi32
  doubleconversion
  gdi32
  glib
  iconv
  icu
  journald
  kernel32
  libatomic
  librt
  lttng_ust
  netapi32
  ole32
  pcre2
  pps
  shell32
  user32
  uuid
  winmm
  ws2_32
network:
  gssapi
  libproxy
  network
  openssl
gui:
  atspi
  d2d1
  d2d1_1
  d3d11
  d3d11_1
  d3d9
  d3dcompiler
  directfb
  drm
  dwrite
  dwrite_1
  dwrite_2
  dxgi
  dxgi1_2
  dxguid
  egl
  fontconfig
  freetype
  gbm
  harfbuzz
  integrityhid
  lgmon
  libinput
  libjpeg
  libmd4c
  libpng
  mtdev
  opengl
  opengl_es2
  openvg
  tslib
  v4l2
  vulkan
  wayland_server
  x11sm
  xcb
  xcb_glx
  xcb_icccm
  xcb_image
  xcb_keysyms
  xcb_randr
  xcb_render
  xcb_renderutil
  xcb_shape
  xcb_shm
  xcb_sync
  xcb_xfixes
  xcb_xinerama
  xcb_xinput
  xcb_xkb
  xcb_xlib
  xkbcommon
  xkbcommon_x11
  xlib
  xrender
widgets:
  gtk3
printsupport:
  cups
sqldrivers:
  db2
  ibase
  mysql
  oci
  odbc
  psql
  sqlite
  sqlite2
  tds	
```
