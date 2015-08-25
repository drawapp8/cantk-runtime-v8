# V8_SRC=/home/samliu/TOOL/v8
# V8BINDING_ROOT=/work/lab/cantk/v8-native-binding-generator/

V8_SRC ?= /home/lixianjing/work/lab/cantk/v8
V8BINDING_ROOT ?= /work/lab/cantk/v8-native-binding-generator/

THIRD_ROOT=../src/third
CFLAGS=-I$(V8_SRC) -I$(V8_SRC)/include -I../src/cantk-rt -I../src/cantk-rt/htmlparser -I$(THIRD_ROOT) \
		-I$(THIRD_ROOT)/nanovg/src -I$(V8BINDING_ROOT) -I$(THIRD_ROOT)/libuv/include\
		-I$(THIRD_ROOT)/libuv/src \
		-DNANOVG_GL2 -DNANOVG_GLEW

VPATH=./:../src/cantk-rt/:../src/cantk-rt/htmlparser:$(THIRD_ROOT)/fossa/:$(THIRD_ROOT)/nanovg/src/:$(THIRD_ROOT)/libuv/src/unix/:$(THIRD_ROOT)/libuv/src
OBJS=main.o \
	Config.o \
	Location.o \
	LocationBinding.o \
	CanvasBinding.o \
	CanvasRenderingContext2dBinding.o \
	ImageBinding.o \
	Native.o \
	Canvas.o  \
	CanvasRenderingContext2d.o   \
	Image.o    \
	nanovg.o \
	color_parser.o \
	utils.o \
	HttpClient.o \
	HttpClientBinding.o fossa.o V8Wrapper.o \
	FileSystemBinding.o  FileSystem.o Screen.o ScreenBinding.o \
	fs-poll.o \
	inet.o \
	threadpool.o \
	uv-common.o \
	version.o \
	async.o \
	core.o \
	dl.o \
	fs.o \
	getaddrinfo.o \
	getnameinfo.o \
	loop-watcher.o \
	loop.o \
	pipe.o \
	poll.o \
	process.o \
	signal.o \
	stream.o \
	tcp.o \
	thread.o \
	timer.o \
	tty.o \
	udp.o \
	linux-core.o \
	linux-inotify.o \
	linux-syscalls.o \
	proctitle.o \
	parse_html.o \
	xml_parser.o

LIBV8_ROOT=$(V8_SRC)/out/x64.debug/obj.target/tools/gyp
LIBICU_ROOT=$(V8_SRC)/out/x64.debug/obj.target/third_party/icu

LIBS=$(LIBV8_ROOT)/libv8_base.a $(LIBV8_ROOT)/libv8_libbase.a \
	$(LIBV8_ROOT)/libv8_snapshot.a $(LIBV8_ROOT)/libv8_libplatform.a $(LIBV8_ROOT)/libv8_nosnapshot.a \
	$(LIBICU_ROOT)/libicui18n.a  $(LIBICU_ROOT)/libicuuc.a $(LIBICU_ROOT)/libicudata.a \
	`pkg-config --cflags libuv --libs` `pkg-config --libs glfw3` -lGL -lGLU -lGLEW -lm  -lpthread  -lstdc++

%.o:%.cpp
	$(CC) -g -c $< $(CFLAGS)
%.o:%.c
	$(CC) -g -c $< $(CFLAGS)

all:$(OBJS)
	$(CC) -g $(OBJS) $(LIBS) -o jsrun 
	mv -f jsrun ../

clean:
	rm -f *.o ../jsrun
uv:
	gcc -g `pkg-config --cflags libuv --libs` uv.c -o uv_test

