
namespace Amalgamation {

	VKInstance::VKInstance()  {}
	VKInstance::VKInstance(const char * Name) { CreateInstance(Name); }
	VKInstance::~VKInstance() { DestroyInstance(); }

}