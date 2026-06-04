./bld/:
	meson setup bld -Dunity:extension_fixture=true

build: ./bld/
	meson compile -C bld

test: build
	meson test -C bld --print-errorlogs

clean:
	rm -rf ./bld/
	rm -rf ./doxy_out/
	rm -rf ./pack/out/

.PHONY: build test clean pack
