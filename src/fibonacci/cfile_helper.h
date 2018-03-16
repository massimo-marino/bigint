/* 
 * File:   cfile_helper.h
 * Author: massimo
 *
 * Created on November 3, 2016, 11:52 AM
 */
#pragma once

#include <fstream>
////////////////////////////////////////////////////////////////////////////////
// BEGIN: ignore the warnings listed below when compiled with clang from here
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
////////////////////////////////////////////////////////////////////////////////
namespace utilities::cfile_helper
{
class cfile_helper final
{
 public:
  enum class fstream_direction : int { fs_NOT_DEFINED, fs_INPUT, fs_OUTPUT };

  cfile_helper () = delete;
  explicit cfile_helper (const cfile_helper& orig) noexcept;
  explicit cfile_helper (const std::string&       file_name = "",
                         const fstream_direction& fs_direction = fstream_direction::fs_NOT_DEFINED) noexcept(false);
  ~cfile_helper ();

  bool is_file_open () const noexcept;
  inline constexpr bool is_file_closed () const noexcept;
  inline constexpr bool is_eof_reached () const noexcept;
  inline constexpr bool is_eof_not_reached () const noexcept;

  std::fstream& get_fstream () const noexcept;
  void set_fstream(const std::string& file_name, const std::ios_base::openmode& mode) const noexcept(false);
  // open file for input
  std::fstream& open_input_file (const std::string& file_name) const noexcept(false);
  // open file for output
  std::fstream& open_output_file (const std::string& file_name) const noexcept(false);

  void close_file() const;

  // get the file size
  std::streamoff file_size() const;
  std::streamoff file_size(std::fstream& f) const;

  // load the whole file, starting from position pos, into the string
  int load_file_in_string (std::string&          string,
                           const std::streampos& pos = 0) const noexcept(false);

 private:
  mutable std::string  m_file_name {};
  mutable std::fstream m_fstream {};
  mutable fstream_direction m_fs_direction {fstream_direction::fs_NOT_DEFINED};
  mutable bool m_file_is_open {false};

  void open_file () const noexcept(false);
  std::fstream& open_file (const std::ios_base::openmode& mode) const noexcept(false);
  inline constexpr void close_fstream () const;
  // set the file as open; set m_file_is_open
  inline void set_file_is_open () const noexcept;
  // set the file as closed; set m_file_is_open
  inline void set_file_is_closed () const noexcept;
  inline void set_file_name (const std::string& file_name) const noexcept;
  inline std::string get_file_name() const noexcept;
  inline void set_fstream_direction (const fstream_direction& fs_direction) const noexcept;
  inline constexpr fstream_direction get_fstream_direction () const noexcept;
};  // class cfile_helper
}  // namespace utilities::cfile_helper
////////////////////////////////////////////////////////////////////////////////
#pragma clang diagnostic pop
// END: ignore the warnings when compiled with clang up to here
