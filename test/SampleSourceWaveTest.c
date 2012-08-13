#include "TestRunner.h"
#include "SampleSourceWave.h"
#include "SampleSource.h"
#include "AudioSettings.h"

static void _sampleSourceWaveSetup(void) {
  initAudioSettings();
}

static void _sampleSourceWaveTeardown(void) {
  freeAudioSettings();
}

static CharString _waveResourceName() {
  CharString resourceName = newCharString();
  copyToCharString(resourceName, "resources/audio/a440-stereo.wav");
  return resourceName;
}

static int _testOpenWaveFile(void) {
  SampleSource s = newSampleSourceWave(_waveResourceName());
  SampleSourceWaveData extraData = s->extraData;
  _assertNotNull(extraData);
  _assert(s->openSampleSource(s, SAMPLE_SOURCE_OPEN_READ));
  _assertIntEquals(s->openedAs, SAMPLE_SOURCE_OPEN_READ);
  _assertIntEquals(s->numChannels, 2);
  _assertDoubleEquals(s->sampleRate, 44100.0);
  return 0;
}

void runSampleSourceWaveFileTests(void);
void runSampleSourceWaveFileTests(void) {
  _startTestSection();
  _runTest("Open file", _testOpenWaveFile, _sampleSourceWaveSetup, _sampleSourceWaveTeardown);
}