all: protoc_caffe app

protoc_caffe: caffe.proto
	protoc --cpp_out=. caffe.proto

app: main.cc caffe.pb.cc
	c++ -std=c++11 main.cc caffe.pb.cc -o app -I/home/roger/usr/include -L/home/roger/usr/lib -lprotobuf 

.PHONY: clean
clean:
	rm -f app caffe.pb.cc caffe.pb.h