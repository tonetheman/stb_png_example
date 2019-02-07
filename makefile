junk : test_image_write.cpp
	g++ -o junk test_image_write.cpp

clean:
	rm -f *.png
	rm -f junk
	rm -f *.o
