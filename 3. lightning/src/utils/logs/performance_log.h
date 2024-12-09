#pragma once

namespace PerformanceLog {
  extern double lastTime;
  extern int nbFrames;
  extern double time_per_frame;
  extern int frame_per_time;

  struct FrameMetric {
    double sec_per_frame;
    int frames_per_sec;
  };

  FrameMetric GetTimePerFrame(double currentTime);
  int GetFramesPerSecond();
}
