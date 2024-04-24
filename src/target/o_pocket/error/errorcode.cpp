#include <string>
#include <stdio.h>
#include "errorcode.h"
#include <mutex>
#include "log.h"
///The default facility
static errfac deffac;
static std::mutex name_mutex;
extern std::map<std::string, errfac> errfac_map{};



///Pointer to default facility
errfac* errfac::default_facility = &deffac;

///Set defaults for log and throw levels.
errfac::errfac (const std::string& name)
  : throw_level (ERROR_PRI_ERROR)
  , log_level (ERROR_PRI_WARNING)
  , name_ (name){}


errfac* errfac::throw_priority (unsigned int level){
  throw_level = (level < ERROR_PRI_INFO)  ? ERROR_PRI_INFO :
                (level > ERROR_PRI_EMERG) ? ERROR_PRI_EMERG :
                                            level;
  return this;
}

errfac* errfac::log_priority (unsigned int level){
  log_level = (level < ERROR_PRI_INFO)  ? ERROR_PRI_INFO :
              (level > ERROR_PRI_EMERG) ? ERROR_PRI_EMERG :
                                          level;
  return this;
}

void errfac::raise (const erc& e){
  if (e.priority_ >= log_level)
    log (e);
  if (e.priority_ >= throw_level){
    // Make sure this erc is not thrown again
    e.active = false;
    printf("will throw e\n");
    throw e;
  }
}

/// Default message the facility name followed by the error code value
std::string errfac::message (const erc& e) const{
  return name_ + ' ' + std::to_string (e.value);
}

/// Logging action. On Windows platform, default is to use dprintf
void errfac::log (const erc& e){
  std::string msg{ "Log -- " + message (e) + "\n" };
  // if (log_level >= ERROR_PRI_ERROR) {
  //   SLOGE("Log -- {} code:{}", name_, e.value);
  // }
  // else if (log_level >= ERROR_PRI_WARNING) {
  //   SLOGW("Log -- {} code:{}", name_, e.value);
  // }
  // else if (log_level >= ERROR_PRI_INFO) {
  //   SLOGI("Log -- {} code:{}", name_, e.value);
  // }
  // else (log_level >= ERROR_PRI_SUCCESS) {
  //   SLOGD("Log -- {} code:{}", name_, e.value);
  // }
  printf (msg.c_str ());
}

void errfac::Default (errfac *facility){
  default_facility = facility? facility : &deffac;
}
errfac* errfac::name(const std::string& in_name) {
  std::lock_guard<std::mutex> lg(name_mutex);
    name_ = in_name;  
    return this;
}
const std::string& errfac::name () const{
  std::lock_guard<std::mutex> lg(name_mutex);
  return name_;
}
/*!
  Default ctor for erc objects creates an inactive error
*/
erc::erc() :
  value (0),
  priority_ (ERROR_PRI_SUCCESS),
  active (false),
  facility_ (errfac::Default ()){}

/*!
  Ctor for a real erc
*/
erc::erc (int v, short int l, errfac* f) :
  value (v),
  priority_ (l),
  facility_ (f? f : errfac::Default ()),
  active (true){}

erc::erc (erc&& other) :
  value (other.value),
  priority_ (other.priority_),
  active (other.active),
  facility_ (other.facility_){
  //we become the active error, the other is deactivated
    other.active = false;
}

erc::~erc () noexcept(false){
// erc::~erc () {
  if (value && active && priority_)
    facility_->raise (*this);
}

erc& erc::operator= (erc&& rhs){
  printf("trigger move =, may be throw erc\n");
  bool rhs_active = rhs.active;
  rhs.active = false; //prevent rhs from throwing if we throw
  if (active && priority_)
    facility_->raise (*this);
  value = rhs.value;
  priority_ = rhs.priority_;
  facility_ = rhs.facility_;
  active = rhs_active;
  return *this;
}

erc::operator int () const{
  active = false;
  return value;
}

erc& erc::reactivate (){
  active = true;
  return *this;
}

erc& erc::deactivate (){
  active = false;
  return *this;
}


