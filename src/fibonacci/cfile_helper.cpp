/* 
 * File:   cfile_helper.cpp
 * Author: massimo
 * 
 * Created on November 3, 2016, 11:52 AM
 */

#include <string>
#include <iostream>

#include "cfile_helper.h"
////////////////////////////////////////////////////////////////////////////////
namespace utilities::cfile_helper
{
cfile_helper::cfile_helper (const std::string&       file_name,
                            const fstream_direction& fs_direction) noexcept(false)
:
m_file_name(file_name),
m_fs_direction(fs_direction),
m_file_is_open(false)
{
  open_file();
}

void
cfile_helper::open_file () const noexcept(false)
{
  std::ios_base::openmode mode;
  
  switch ( get_fstream_direction() )
  {
    case cfile_helper::fstream_direction::fs_INPUT:
    {
      mode = std::ios_base::in | std::ios_base::ate;
    }
    break;
    
    case cfile_helper::fstream_direction::fs_OUTPUT:
    {
      mode = std::ios_base::out | std::ios_base::ate;
    }
    break;

    case cfile_helper::fstream_direction::fs_NOT_DEFINED:
    {
      return;
    }
  }
  open_file(mode); 
}

cfile_helper::~cfile_helper ()
{
  close_fstream();
}

inline
void
cfile_helper::set_file_name (const std::string& file_name) const noexcept
{
  m_file_name = file_name;
}

inline
std::string
cfile_helper::get_file_name () const noexcept
{
  return m_file_name;
}

inline
void
cfile_helper::set_fstream_direction (const fstream_direction& fs_direction) const noexcept
{
  m_fs_direction = fs_direction;
}

inline constexpr
cfile_helper::fstream_direction
cfile_helper::get_fstream_direction () const noexcept
{
  return m_fs_direction;
}

std::fstream&
cfile_helper::open_file (const std::ios_base::openmode& mode) const noexcept(false)
{
  set_fstream(get_file_name(), mode);
  if ( get_fstream().is_open() )
  {
    set_file_is_open();
  }
  return get_fstream();
}

std::fstream&
cfile_helper::open_input_file (const std::string& file_name) const noexcept(false)
{
  set_file_name(file_name);
  set_fstream_direction(fstream_direction::fs_INPUT);
  set_fstream(file_name, std::ios_base::in | std::ios_base::ate);
  if ( get_fstream().is_open() )
  {
    set_file_is_open();
  }
  return get_fstream();
}

std::fstream&
cfile_helper::open_output_file (const std::string& file_name) const noexcept(false)
{
  set_file_name(file_name);
  set_fstream_direction(fstream_direction::fs_OUTPUT);
  set_fstream(file_name, std::ios_base::out | std::ios_base::ate);
  if ( get_fstream().is_open() )
  {
    set_file_is_open();
  }
  return get_fstream();
}

void
cfile_helper::set_fstream(const std::string& file_name, const std::ios_base::openmode& mode) const noexcept(false)
{
  m_fstream = std::fstream{file_name, mode};
}

std::fstream&
cfile_helper::get_fstream () const noexcept
{
  return m_fstream;
}

inline
void
cfile_helper::close_file () const
{
  close_fstream();
}

inline constexpr
void
cfile_helper::close_fstream () const
{
  get_fstream().close();
  set_file_is_closed();
}

inline
void
cfile_helper::set_file_is_open () const noexcept
{
  m_file_is_open = true;
}

inline
void
cfile_helper::set_file_is_closed () const noexcept
{
  m_file_is_open = false;
}

bool
cfile_helper::is_file_open () const noexcept
{
  return (true == m_file_is_open);
}

inline constexpr
bool
cfile_helper::is_file_closed () const noexcept
{
  return (false == m_file_is_open);
}

inline constexpr
bool
cfile_helper::is_eof_reached () const noexcept
{
  return ( true == get_fstream().eof());
}

inline constexpr
bool
cfile_helper::is_eof_not_reached () const noexcept
{
  return (false == get_fstream().eof());
}

std::streamoff
cfile_helper::file_size() const
{
  // save in a temp the current position of the stream
  std::fstream::pos_type current_pos = get_fstream().tellg();
  if ( (-1) == current_pos )
  {
    return -1;
  }
  // find out the file size
  get_fstream().seekg(0,std::fstream::end);
  std::fstream::pos_type end_pos = get_fstream().tellg();
  // restore the stream to the position saved
  get_fstream().seekg(current_pos);

  return end_pos;
}

std::streamoff
cfile_helper::file_size(std::fstream& f) const
{
  // save in a temp the current position of the stream
  std::fstream::pos_type current_pos = f.tellg();
  if ( (-1) == current_pos )
  {
    return -1;
  }
  // find out the file size
  f.seekg(0,std::fstream::end);
  std::fstream::pos_type end_pos = f.tellg();
  // restore the stream to the position saved
  f.seekg(current_pos);

  return end_pos;
}

//
// cfile_helper::load_file_in_string
//
// Purpose: Load the content of the open file in a string starting from streampos pos
//
// Returns:  0 if OK
//          -1 if file is not open
//          -2 if the memory's size to be allocated is <= 0
//          -3 if seekg() throws an exception
//          -4 if tellg() throws an exception
//          -5 if seekg() throws an exception
//          -6 if read()  throws an exception
//          -7 if new     throws an exception
//
int
cfile_helper::load_file_in_string (std::string&          string,
                                   const std::streampos& pos) const noexcept(false)
{
  if ( false == is_file_open() )
  {
    return(-1);  
  }

  // Determine the file size
  try
  {
    get_fstream().seekg(0, std::ios::end);
  }
  catch (...)
  {
    return (-3);  
  }

  size_t uiFile_Size {};
  try
  {
    uiFile_Size = static_cast<size_t>(get_fstream().tellg());
  }
  catch (...)
  {
    return (-4);
  }

  if ( (static_cast<signed long>(uiFile_Size) - static_cast<signed long>(pos)) <= 0 )
  {
    return (-2);  
  }

  try
  {
    // Set the file pointer to the position pos
    get_fstream().seekg(pos, std::ios::beg);
  }
  catch (...)
  {
    return (-5);
  }

  char* cBuffer = nullptr;
  try
  {
    // Allocate the needed memory
    cBuffer = new char[uiFile_Size - static_cast<size_t>(pos)];
  }
  catch (...)
  {
    return -7;
  }

  try
  {
    // Load the file
    get_fstream().read(reinterpret_cast<char *>(cBuffer), static_cast<long>(uiFile_Size));
  }
  catch (...)
  {
    return (-6);
  }
  string.assign(reinterpret_cast<char *>(cBuffer), uiFile_Size);
  delete[] cBuffer;

  return(0);
}
}  // namespace utilities::cfile_helper
