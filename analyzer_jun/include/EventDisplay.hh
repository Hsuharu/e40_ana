/**
 *  file: EventDisplay.hh
 *  date: 2017.04.10
 *
 */

#ifndef EVENT_DISPLAY_HH
#define EVENT_DISPLAY_HH

#include "ThreeVector.hh"
#include "DetectorID.hh"

class DCLocalTrack;

class TApplication;
class TBox;
class TBRIK;
class TCanvas;
class TFile;
class TGeometry;
class TGraph;
class TH1;
class TH2;
class TLatex;
class TMarker;
class TMarker3DBox;
class TMixture;
class TNode;
class TPad;
class TPave;
class TPaveLabel;
class TPaveText;
class TPolyLine;
class TPolyLine3D;
class TPolyMarker;
class TPolyMarker3D;
class TROOT;
class TRint;
class TRotMatrix;
class TStyle;
class TTRD1;
class TTRD2;
class TTUBS;
class TView;

//______________________________________________________________________________
class EventDisplay //: public TObject
{
public:
  static EventDisplay&      GetInstance( void );
  static const std::string& ClassName( void );
  ~EventDisplay( void );

private:
  EventDisplay( void );
  EventDisplay( const EventDisplay& );
  EventDisplay& operator =( const EventDisplay& );

private:
  bool                       m_is_ready;
  TApplication              *m_theApp;
  TGeometry                 *m_geometry;
  TNode                     *m_node;
  TCanvas                   *m_canvas;
  TCanvas                   *m_canvas_vertex;
  TCanvas                   *m_canvas_hist;
  TCanvas                   *m_canvas_hist2;
  TCanvas                   *m_canvas_hist3;
  TH1                       *m_hist_vertex_x;
  TH1                       *m_hist_vertex_y;
  TH1                       *m_hist_p;
  TH1                       *m_hist_m2;
  TH2                       *m_hist_bh2;
  TH2                       *m_hist_sft_x;
  TH2                       *m_hist_sft_u;
  TH2                       *m_hist_sft_v;
  TH2                       *m_hist_sch;
  TH2                       *m_hist_tof;
  TH2                       *m_hist_sdc1;
  TH2                       *m_hist_sdc1p;
  TH2                       *m_hist_sdc2_l;
  TH2                       *m_hist_sdc2_t;
  TH2                       *m_hist_sdc2p_l;
  TH2                       *m_hist_sdc2p_t;
  TH2                       *m_hist_sdc3_l;
  TH2                       *m_hist_sdc3_t;
  TH2                       *m_hist_sdc3p_l;
  TH2                       *m_hist_sdc3p_t;

  TH2                       *m_hist_bc3;
  TH2                       *m_hist_bc3p;
  TH2                       *m_hist_bc3u;
  TH2                       *m_hist_bc3up;
  TH2                       *m_hist_bc3v;
  TH2                       *m_hist_bc3vp;
  TH2                       *m_hist_bc4;
  TH2                       *m_hist_bc4p;
  TH2                       *m_hist_bc4u;
  TH2                       *m_hist_bc4up;
  TH2                       *m_hist_bc4v;
  TH2                       *m_hist_bc4vp;
  TH1                       *m_hist_bc3_time;
  TH1                       *m_hist_bc3p_time;
  TH1                       *m_hist_bc4_time;
  TH1                       *m_hist_bc4p_time;

  TNode                     *m_target_node;
  TNode                     *m_kurama_inner_node;
  TNode                     *m_kurama_outer_node;
  TNode                     *m_BH2wall_node;
  std::vector<TNode*>        m_BH2seg_node;
  std::vector<TNode*>        m_BC3x1_node;
  std::vector<TNode*>        m_BC3x2_node;
  std::vector<TNode*>        m_BC3v1_node;
  std::vector<TNode*>        m_BC3v2_node;
  std::vector<TNode*>        m_BC3u1_node;
  std::vector<TNode*>        m_BC3u2_node;
  std::vector<TNode*>        m_BC4u1_node;
  std::vector<TNode*>        m_BC4u2_node;
  std::vector<TNode*>        m_BC4v1_node;
  std::vector<TNode*>        m_BC4v2_node;
  std::vector<TNode*>        m_BC4x1_node;
  std::vector<TNode*>        m_BC4x2_node;
  std::vector<TNode*>        m_SFTu_node;
  std::vector<TNode*>        m_SFTv_node;
  std::vector<TNode*>        m_SFTx_node;
  std::vector<TNode*>        m_SDC1v1_node;
  std::vector<TNode*>        m_SDC1v2_node;
  std::vector<TNode*>        m_SDC1x1_node;
  std::vector<TNode*>        m_SDC1x2_node;
  std::vector<TNode*>        m_SDC1u1_node;
  std::vector<TNode*>        m_SDC1u2_node;
  std::vector<TNode*>        m_SDC2x1_node;
  std::vector<TNode*>        m_SDC2x2_node;
  std::vector<TNode*>        m_SDC2y1_node;
  std::vector<TNode*>        m_SDC2y2_node;
  std::vector<TNode*>        m_SDC3y1_node;
  std::vector<TNode*>        m_SDC3y2_node;
  std::vector<TNode*>        m_SDC3x1_node;
  std::vector<TNode*>        m_SDC3x2_node;
  std::vector<TNode*>        m_SSD1y1_node;
  TNode                     *m_FBHwall_node;
  std::vector<TNode*>        m_FBHseg_node;
  TNode                     *m_SCHwall_node;
  std::vector<TNode*>        m_SCHseg_node;
  TNode                     *m_FBT1d1wall_node;
  std::vector<TNode*>        m_FBT1d1seg_node;
  TNode                     *m_FBT1u1wall_node;
  std::vector<TNode*>        m_FBT1u1seg_node;
  TNode                     *m_FBT1d2wall_node;
  std::vector<TNode*>        m_FBT1d2seg_node;
  TNode                     *m_FBT1u2wall_node;
  std::vector<TNode*>        m_FBT1u2seg_node;
  TNode                     *m_FBT2d1wall_node;
  std::vector<TNode*>        m_FBT2d1seg_node;
  TNode                     *m_FBT2u1wall_node;
  std::vector<TNode*>        m_FBT2u1seg_node;
  TNode                     *m_FBT2d2wall_node;
  std::vector<TNode*>        m_FBT2d2seg_node;
  TNode                     *m_FBT2u2wall_node;
  std::vector<TNode*>        m_FBT2u2seg_node;
  TNode                     *m_TOFwall_node;
  std::vector<TNode*>        m_TOFseg_node;
  TPolyMarker3D             *m_init_step_mark;
  std::vector<TPolyLine3D*>  m_BcOutTrack;
  std::vector<TPolyLine3D*>  m_SdcInTrack;
  std::vector<TPolyLine3D*>  m_SdcOutTrack;
  TPolyMarker3D             *m_kurama_step_mark;
  // vertex
  TBox                      *m_TargetXZ_box;
  TBox                      *m_TargetYZ_box;
  TBox                      *m_EmulsionXZ_box;
  TBox                      *m_EmulsionYZ_box;
  std::vector<TBox*>         m_FBHseg_box;
  TH1                       *m_SSD_x_hist;
  TH1                       *m_SSD_y_hist;
  TMarker                   *m_VertexPointXZ;
  TMarker                   *m_VertexPointYZ;
  std::vector<TPolyLine*>    m_BcOutXZ_line;
  std::vector<TPolyLine*>    m_BcOutYZ_line;
  std::vector<TPolyLine*>    m_SdcInXZ_line;
  std::vector<TPolyLine*>    m_SdcInYZ_line;
  TPolyMarker               *m_KuramaMarkVertexX;
  TPolyMarker               *m_KuramaMarkVertexY;
  TPolyLine                 *m_MissMomXZ_line;
  TPolyLine                 *m_MissMomYZ_line;

public:
  bool Initialize( void );
  bool IsReady( void ) const { return m_is_ready; }
  bool ConstructEmulsion( void );
  bool ConstructTarget( void );
  bool ConstructBH2( void );
  bool ConstructKURAMA( void );
  bool ConstructCollimator( void );
  bool ConstructBcOut( void );
  bool ConstructSdcIn( void );
  bool ConstructSdcOut( void );
  bool ConstructSSD( void );
  bool ConstructFBH( void );
  bool ConstructSCH( void );
  bool ConstructFBT( void );
  bool ConstructTOF( void );
  void DrawInitTrack( int nStep, ThreeVector *StepPoint );
  void DrawInitTrack( void );
  void DrawHitWire( int lid, int hit_wire,
		    bool range_check=true, bool tdc_check=true );
  void DrawTrackWire( int lid, int hit_wire, int it );
  void DrawText( double xpos, double ypos, const std::string& arg );
  void DrawHitHodoscope( int lid, int seg, int Tu=1, int Td=1 );
  void DrawBcOutLocalTrack( DCLocalTrack *tp );
  void DrawBcOutLocalTrack( double x0, double y0, double u0, double v0 );
  void DrawSdcInLocalTrack( DCLocalTrack *tp );
  void DrawSdcOutLocalTrack( DCLocalTrack *tp );
  void DrawSsdHit( int lid, int seg, double de );
  void DrawVertex( const ThreeVector& vertex );
  void DrawKuramaTrack( int nStep, ThreeVector *StepPoint, int Polarity );
  void DrawTarget( void );
  void DrawMissingMomentum( const ThreeVector& mom,
			    const ThreeVector& pos );
  void DrawMomentum( double momentum );
  void DrawMassSquare( double mass_square );
  void DrawBH2( int seg, int tdc );
  void DrawSFT_X( int seg, int tdc );
  void DrawSFT_U( int seg, int tdc );
  void DrawSFT_V( int seg, int tdc );
  void DrawSCH( int seg, int tdc );
  void DrawTOF( int seg, int tdc );
  void DrawBcOutHit(int layer,  int wire, int tdc );
  void DrawBC3( int wire, int tdc );
  void DrawBC3p( int wire, int tdc );
  void DrawBC4( int wire, int tdc );
  void DrawBC4p( int wire, int tdc );
  void DrawSDC1( int wire, int tdc );
  void DrawSDC1p( int wire, int tdc );
  void DrawSDC2_Leading( int wire, int tdc );
  void DrawSDC2_Trailing( int wire, int tdc );
  void DrawSDC2p_Leading( int wire, int tdc );
  void DrawSDC2p_Trailing( int wire, int tdc );
  void DrawSDC3_Leading( int wire, int tdc );
  void DrawSDC3_Trailing( int wire, int tdc );
  void DrawSDC3p_Leading( int wire, int tdc );
  void DrawSDC3p_Trailing( int wire, int tdc );
  void UpdateHist( void );
  void EndOfEvent( void );
  void ResetVisibility( void );
  void CalcRotMatrix( double TA, double RA1, double RA2, double *rotMat );
  int  GetCommand( void ) const;
  void Run( bool flag=kTRUE );

private:
  void ResetVisibility( TNode *& node, Color_t c=kWhite );
  void ResetVisibility( std::vector<TNode*>& node, Color_t c=kWhite );
  void ResetHist( void );
};

//______________________________________________________________________________
inline EventDisplay&
EventDisplay::GetInstance( void )
{
  static EventDisplay g_instance;
  return g_instance;
}

//______________________________________________________________________________
inline const std::string&
EventDisplay::ClassName( void )
{
  static std::string g_name("EventDisplay");
  return g_name;
}

#endif
