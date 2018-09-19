// -*- C++ -*-

#include <DAQNode.hh>
#include <Unpacker.hh>
#include <UnpackerManager.hh>

#include "Utility.hh"

namespace
{
  const std::string& class_name("TimeStamp");
  using namespace hddaq::unpacker;
  const UnpackerManager& gUnpacker = GUnpacker::get_instance();
}

namespace utility
{
//____________________________________________________________________________
  UInt_t
  EBDataSize( void )
  {
    static const Int_t NodeIdEB = gUnpacker.get_fe_id("k18eb");
    return gUnpacker.get_node_header(NodeIdEB, DAQNode::k_data_size);
  }

//____________________________________________________________________________
  UInt_t
  UnixTime( void )
  {
    static const Int_t NodeIdEB = gUnpacker.get_fe_id("k18eb");
    return gUnpacker.get_node_header(NodeIdEB, DAQNode::k_unix_time);
  }

//____________________________________________________________________________
  TTimeStamp
  TimeStamp( void )
  {
    TTimeStamp s( UnixTime() );
    s.Add( -s.GetZoneOffset() );
    return s;
  }
}
