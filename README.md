## Trace Event Library
The trace event library is a part of the Chromium project. I created this project so that:
 * It does not rely on Chromium's build system anymore.
 * It is much easier to port to platforms that Chromium doesn't support.
 * A simple and small project like this can be integrated into your project easily.

The generated trace event log can be simply processed with the [Catapult project](https://github.com/catapult-project/catapult) or viewed with Chrome's [about:tracing](http://dev.chromium.org/developers/how-tos/trace-event-profiling-tool)
