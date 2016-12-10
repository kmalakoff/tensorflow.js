#include "train.h"
#include "graph.h"
#include "operation.h"
#include "../tensorflow/train.h"
#include "../lib/conversions.h"

namespace addons {

using namespace v8;

NAN_MODULE_INIT(Train::Init) {
  Nan::Persistent<Object> inner;
  Local<Object> obj = Nan::New<Object>();
  inner.Reset(obj);

  Nan::SetMethod(obj, "GradientDescentOptimizer", GradientDescentOptimizer);

  target->Set(Nan::New("Train").ToLocalChecked(), obj);
};

NAN_METHOD(Train::GradientDescentOptimizer) {
  TF_Graph* graph = ObjectWrap::Unwrap<addons::Graph>(info[0]->ToObject())->ref();
  TF_Operation* arg0 = ObjectWrap::Unwrap<Operation>(info[0]->ToObject())->ref(); 
  TF_Operation* result = tensorflow::Train::GradientDescentOptimizer(graph, arg0);

  info.GetReturnValue().Set((new Operation(result))->ToValue());
}

} // namespace addons
