all:	doc quasi

doc:
	max2html --out documentation/openxds.core.base.Math.html source/mtx/Math.mtx.txt

quasi:
	quasi -f . source/mtx/*mtx*

clean:
	rm -rf obj
	rm -rf lib
