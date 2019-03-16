#include <node.h>
#include "distributedId.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  DistributedID::Init(exports);
}

NODE_MODULE(addon, InitAll);
