

#include"PangolinViewer.h"
#include "Map.h"
#include "Camera.h"
//#include "Frame.h"
//#include "KeyFrame.h"


int main(int argc, char **argv) {
  ORB_SLAM2::ORBVocabulary voc;
  voc.loadFromBinaryFile("/home/king/Documents/king/ORB_SLAM2_MAP/Vocabulary/ORBvoc.bin");
  
  const string settings_file = "/home/king/Documents/king/ORB_SLAM2_MAP/Examples/RGB-D/TUM3.yaml";
  ORB_SLAM2::Camera::Load(settings_file);

  ORB_SLAM2::Map map;
  string mapename;
  if (argc> 1) mapename = argv[1];
  else mapename = "/home/king/Documents/king/ORB_SLAM2_MAP/tum3_map.bin";
  std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
  map.Load(mapename, voc);
  std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();
  double tsave= std::chrono::duration_cast<std::chrono::duration<double> >(t4 - t3).count();
  cerr << "loaded in " << tsave << endl;
  if (0)
  {
	vector<ORB_SLAM2::KeyFrame*> vkf = map.GetAllKeyFrames();
	for (unsigned int i=0; i<vkf.size(); i++) {
	  ORB_SLAM2::KeyFrame* kf = vkf[i];
	  cerr << kf->mnId << " " << kf->mBowVec.size() << " " << kf->mFeatVec.size();
	  //for (unsigned int j=0; j<kf->mBowVec.size(); j++)
	  //	if ((j%51)==0) cerr << " " << kf->mBowVec[j];
	  //for (unsigned int j=0; j<kf->mFeatVec.size(); j++)
	  //	  if ((j%51)==0) cerr << " " << kf->mFeatVec[j];
	  cerr << endl;
	}
  } 

  ORB_SLAM2::PangolinViewer viewer(settings_file);
  viewer.RegisterMap(&map);
  viewer.Run();
  return 0;
}
