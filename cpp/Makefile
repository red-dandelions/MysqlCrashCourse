DIRS = util chapter4 chapter5 chapter6 chapter7 chapter8 chapter9 chapter10	\
			 chapter11 chapter12 chapter13 chapter14 chapter15 chapter16 chapter17

all:
	@for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1;\
	done
clean:
	@for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
