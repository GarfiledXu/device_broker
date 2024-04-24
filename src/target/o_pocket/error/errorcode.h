#ifndef ERROR_CODE_H
#define ERROR_CODE_H
#include <string>
#include <map>
class erc;
class errfac;
extern std::map<std::string, errfac> errfac_map;
// #define ERRFAC_REGI(in_name, log_pri, throw_pri) errfac_map[in_name].throw_priority(throw_pri);errfac_map[in_name].log_priority(log_pri);errfac_map[in_name].name(in_name);
#define ERRFAC_REGI(in_name, log_pri, throw_pri) errfac_map[in_name].throw_priority(throw_pri)->log_priority(log_pri)->name(in_name)
#define ERRFAC_REGI_NAME(in_name) errfac_map[in_name].throw_priority(ERROR_PRI_ERROR)->log_priority(ERROR_PRI_WARNING)->name(in_name)
#define ERRFAC_REF(in_name) &(errfac_map[in_name])
#define ERRFAC_DEFAULT() errfac::Default()
// error 级别
#define ERROR_PRI_SUCCESS     0  ///< always    not logged,   not thrown
#define ERROR_PRI_INFO        1  ///< default   not logged,   not thrown
#define ERROR_PRI_NOTICE      2  ///< default   not logged,   not thrown
#define ERROR_PRI_WARNING     3  ///< default   logged,       not thrown
#define ERROR_PRI_ERROR       4  ///< default   logged,       thrown
#define ERROR_PRI_CRITICAL    5  ///< default   logged,       thrown
#define ERROR_PRI_ALERT       6  ///< default   logged,       thrown
#define ERROR_PRI_EMERG       7  ///< always    logged,       thrown


class errfac{
  friend class erc;
public:
  // constructors/destructor
  errfac (const std::string& name = "Error");
  
  /// set throw priority
  // void throw_priority (unsigned int pri);
  //xjf modify
  errfac* throw_priority (unsigned int pri);

  /// get throw priority
  unsigned int throw_priority () const;

  /// set log priority
  // void log_priority (unsigned int pri);
  //xjf add
  errfac* log_priority (unsigned int pri);

  /// get log priority
  unsigned int log_priority () const;

  /// return message to be logged
  virtual std::string message (const erc& e) const;

  /// get name
  const std::string& name () const;
  //xjf add
  errfac* name(const std::string& in_name);

  /// set default facility
  static void Default (errfac *f);

  /// get default facility
  static errfac* Default ();
  //存疑
  // static errfac* Default (const std::string& name, unsigned int log_pri = ERROR_PRI_WARNING, unsigned int  throw_pri = ERROR_PRI_ERROR);

protected:
  virtual void raise (const erc& e);
  virtual void log (const erc& e);

private:
  unsigned int    log_level;
  unsigned int    throw_level;
  std::string     name_;
  static errfac*  default_facility;
};

//xjf modify: to inherit exception
// class erc : public std::exception{
class erc {
public:
  erc ();
  erc (int value, short int priority=ERROR_PRI_ERROR, errfac* f = 0);
  erc(const erc& other) = default;
  erc (erc&& other);

  //xjf add not override
  const char* what() const noexcept {
    active = false;
    return message().c_str();
  }

  ~erc () noexcept(false) ;
  // virtual ~erc ()  ;
  erc& operator= (const erc& rhs) = default;
  erc& operator= (erc&& rhs);
  operator int () const;
  
  ///Return priority value
  unsigned int priority () const;

  ///Return reference to facility
  errfac& facility () const;

  erc& reactivate ();
  erc& deactivate ();

  int code () const;

  ///Get logging message
  std::string  message () const;

private:
  //bit fields
  int             value : 24;
  unsigned int    priority_ : 4;
  mutable unsigned int active : 1;

  errfac*         facility_;

  friend class errfac;
};

inline unsigned int  errfac::throw_priority () const {
  return throw_level;
}

inline unsigned int errfac::log_priority () const {
  return log_level;
}



inline errfac* errfac::Default (){
  return default_facility;
}

//存疑
// inline errfac* errfac::Default(const std::string& name, unsigned int log_pri = ERROR_PRI_WARNING, unsigned int  throw_pri = ERROR_PRI_ERROR) {
//   default_facility->name_ = name;
//   default_facility->log_level = log_pri;
//   default_facility->throw_level = throw_pri;
//   return default_facility;
// }

inline unsigned int erc::priority () const{
  return priority_;
}

inline errfac& erc::facility () const {
  return *facility_;
}

inline int erc::code () const{
  return value;
}

inline std::string erc::message () const{
  return facility_->message (*this);
}

#define ERR_SUCCESS (erc ())

#endif