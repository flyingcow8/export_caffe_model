#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include "caffe.pb.h"
using namespace std;
using google::protobuf::io::FileOutputStream;
using google::protobuf::Message;

void WriteProtoToTextFile(const Message& proto, const char* filename) {
  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  FileOutputStream* output = new FileOutputStream(fd);
  google::protobuf::TextFormat::Print(proto, output);
  delete output;
  close(fd);
}

int main(int argc, char* argv[]) {
  caffe::NetParameter net;
  net.set_name("SampleCaffeModel");
  caffe::LayerParameter *input = net.add_layer();
  input->set_name("data");
  input->set_type("input");
  input->add_top("data");
  caffe::InputParameter *input_param = input->mutable_input_param();
  caffe::BlobShape *input_shape = input_param->add_shape();
  input_shape->add_dim(1);
  input_shape->add_dim(3);
  input_shape->add_dim(451);
  input_shape->add_dim(451);
  WriteProtoToTextFile(net, "sample.prototxt");
  return 0;
}