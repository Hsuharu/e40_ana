/**
 *  file: DebugCounter.hh
 *  date: 2017.04.10
 *
 */

#ifndef DEBUG_COUNTER_HH
#define DEBUG_COUNTER_HH

#include <map>
#include <string>
#include <vector>

#include <std_ostream.hh>

//_____________________________________________________________________
namespace debug
{
  class ObjectCounter
  {
  public:
    static ObjectCounter& GetInstance( void );
    ~ObjectCounter( void );

  private:
    ObjectCounter( void );
    ObjectCounter( const ObjectCounter& );
    ObjectCounter& operator =( const ObjectCounter& );

  private:
    typedef std::map<std::string,int> ObjectMap;
    typedef ObjectMap::const_iterator ObjectIter;
    ObjectMap m_map;

  public:
    void check( const std::string& arg="" ) const;
    void print( const std::string& arg="" ) const;

  public:
    static void decrease( const std::string& key );
    static void increase( const std::string& key );
  };

  //_____________________________________________________________________
  inline ObjectCounter&
  ObjectCounter::GetInstance( void )
  {
    static ObjectCounter g_instance;
    return g_instance;
  }

  //_____________________________________________________________________
  inline void
  ObjectCounter::decrease( const std::string& key )
  {
#ifdef MemoryLeak
    --(GetInstance().m_map[key]);
#endif
  }

  //_____________________________________________________________________
  inline void
  ObjectCounter::increase( const std::string& key )
  {
#ifdef MemoryLeak
    ++(GetInstance().m_map[key]);
#endif
  }

}

#endif
