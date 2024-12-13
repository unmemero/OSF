all:
	gcc -Wall -O3 -o runparallel runparallel.c

run:
	./runparallel

clean:
	rm -f runparallel

push:
	@read -p "Enter commit message: " message; \
	git pull origin main; \
	git add .; \
	git commit -m "$$message"; \
	git push origin main

commit:
	@read -p "Enter commit message: " message; \
	git add .; \
	git commit -m "$$message"
