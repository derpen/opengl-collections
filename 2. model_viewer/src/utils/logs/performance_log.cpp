#include "performance_log.h"

namespace pl {
  double lastTime = 0.0;
  int nbFrames = 0;
  double time_per_frame = 0.0;
  int frame_per_time = 0;

  // Measured in time taken per frame (ex: 12 ms/frames)
  // and not how many frames per sec (ex: 60 frames/second)
  FrameMetric GetTimePerFrame(double currentTime){
    nbFrames++;

    if ( currentTime - lastTime >= 1.0 ){
      time_per_frame = 1000.0/double(nbFrames);
      frame_per_time = nbFrames;
      nbFrames = 0;
      lastTime += 1.0;
    }

    return { time_per_frame, frame_per_time };
  };
}
