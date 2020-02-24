sub:
	$(MAKE) -C src
	mv src/app.out ./

install:
	cp -v ./app.out /usr/local/bin/nodemonitor
	chmod +x /usr/local/bin/nodemonitor

clean:
	rm -rf src/*.o
	rm -rf src/*.out
	rm -rf ./app.out