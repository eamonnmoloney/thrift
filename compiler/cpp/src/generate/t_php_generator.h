#ifndef T_PHP_GENERATOR_H
#define T_PHP_GENERATOR_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "t_oop_generator.h"

/**
 * Java code generator.
 *
 * @author Mark Slee <mcslee@facebook.com>
 */
class t_php_generator : public t_oop_generator {
 public:
  t_php_generator(bool binary_inline=false) {
    binary_inline_ = binary_inline;
    if (binary_inline_) {
      T_PHP_DIR = "gen-phpi";
    } else {
      T_PHP_DIR = "gen-php";
    }
  }
  
  ~t_php_generator() {}

  /** Init and close methods */

  void init_generator(t_program *tprogram);
  void close_generator(t_program *tprogram);

  /** Program-level generation functions */

  void generate_typedef  (t_typedef*  ttypedef);
  void generate_enum     (t_enum*     tenum);
  void generate_struct   (t_struct*   tstruct);
  void generate_xception (t_struct*   txception);
  void generate_service  (t_service*  tservice);


  void generate_php_struct(t_struct* tstruct, bool is_exception);
  void generate_php_struct_definition(std::ofstream& out, t_struct* tstruct, bool is_xception=false);
  void generate_php_struct_reader(std::ofstream& out, t_struct* tstruct);
  void generate_php_struct_writer(std::ofstream& out, t_struct* tstruct);

  void generate_php_function_helpers  (t_function* tfunction);

  /** Service-level generation functions */

  void generate_service_helpers(t_service*  tservice);
  void generate_service_interface (t_service* tservice);
  void generate_service_client    (t_service* tservice);

  /** Serialization constructs */

  void generate_deserialize_field        (std::ofstream &out,
                                          t_field*    tfield, 
                                          std::string prefix="",
                                          bool inclass=false);
  
  void generate_deserialize_struct       (std::ofstream &out,
                                          t_struct*   tstruct,
                                          std::string prefix="");
  
  void generate_deserialize_container    (std::ofstream &out,
                                          t_type*     ttype,
                                          std::string prefix="");
  
  void generate_deserialize_set_element  (std::ofstream &out,
                                          t_set*      tset,
                                          std::string prefix="");

  void generate_deserialize_map_element  (std::ofstream &out,
                                          t_map*      tmap,
                                          std::string prefix="");

  void generate_deserialize_list_element (std::ofstream &out,
                                          t_list*     tlist,
                                          std::string prefix="");

  void generate_serialize_field          (std::ofstream &out,
                                          t_field*    tfield,
                                          std::string prefix="");

  void generate_serialize_struct         (std::ofstream &out,
                                          t_struct*   tstruct,
                                          std::string prefix="");

  void generate_serialize_container      (std::ofstream &out,
                                          t_type*     ttype,
                                          std::string prefix="");

  void generate_serialize_map_element    (std::ofstream &out,
                                          t_map*      tmap,
                                          std::string kiter,
                                          std::string viter);

  void generate_serialize_set_element    (std::ofstream &out,
                                          t_set*      tmap,
                                          std::string iter);

  void generate_serialize_list_element   (std::ofstream &out,
                                          t_list*     tlist,
                                          std::string iter);

  /** Helper rendering functions */

  std::string php_includes();
  std::string type_name(t_type* ttype);
  std::string base_type_name(t_base_type::t_base tbase);
  std::string declare_field(t_field* tfield, bool init=false, bool obj=false);
  std::string function_signature(t_function* tfunction, std::string prefix="");
  std::string argument_list(t_struct* tstruct);
  std::string type_to_enum(t_type* ttype);

 private:

  /** File streams */
  char* T_PHP_DIR;

  std::ofstream f_types_;
  std::ofstream f_helpers_;
  std::ofstream f_service_;

  /** Generate protocol-independent template? Or Binary inline code? */

  bool binary_inline_;

};

#endif
