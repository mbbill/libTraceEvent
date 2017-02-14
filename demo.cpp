#include <iostream>
#include <string>
#include "base/logging.h"
#include "base/bind.h"
//#include "base/base64.h"
//#include "base/run_loop.h"
#include "base/memory/ref_counted_memory.h"
#include "base/trace_event/trace_event.h"
#include "base/trace_event/trace_buffer.h"
#include "base/trace_event/trace_log.h"

using namespace std;
using namespace base;

static const char EVENT_CATEGORIES[] = "test_categories";

////////////////////////////////////////////////////////////////////////////////
void DemoLog() {
    TRACE_EVENT0(EVENT_CATEGORIES, "DemoLog");
    //LOG(INFO) << "Demo INFO Log";
    //LOG(ERROR) << "Demo ERROR Log";
}

////////////////////////////////////////////////////////////////////////////////
void DemoTraceEventBegin() {
    cout << "{\"traceEvents\": [" << endl;

    string categories = EVENT_CATEGORIES;

    trace_event::TraceLog::GetInstance()->SetEnabled(
        trace_event::TraceConfig(categories, trace_event::RECORD_UNTIL_FULL),
        trace_event::TraceLog::RECORDING_MODE);
}

/*
static void OnTraceDataCollected(
        Closure quit_closure,
        trace_event::TraceResultBuffer* buffer,
        const scoped_refptr<RefCountedString>& json_events_str,
        bool has_more_events) {
    buffer->AddFragment(json_events_str->data());
    if (!has_more_events) {
        quit_closure.Run();
    }
}

static void TraceOutputCallback(const std::string& data) {
    cout << data << endl;
}
*/
static void new_output_callback (const scoped_refptr<RefCountedString>& json_events_str,
          bool has_more_events) {
    cout << json_events_str->data();
}

void DemoTraceEventEnd() {
    trace_event::TraceLog::GetInstance()->SetDisabled();

    //trace_event::TraceResultBuffer buffer;
    //buffer.SetOutputCallback(Bind(&TraceOutputCallback));

    //RunLoop run_loop;
    //trace_event::TraceLog::GetInstance()->Flush(
    //    Bind(&OnTraceDataCollected, run_loop.QuitClosure(), Unretained(&buffer)));

    //run_loop.Run();
    trace_event::TraceLog::GetInstance()->Flush(Bind(&new_output_callback));
    cout << "]}" << endl;
}

////////////////////////////////////////////////////////////////////////////////
void NestedTraceLog1() {
    TRACE_EVENT0(EVENT_CATEGORIES, "NestedTraceLog1");
    PlatformThread::Sleep(TimeDelta::FromMilliseconds(100));
}

void NestedTraceLog2() {
    TRACE_EVENT0(EVENT_CATEGORIES, "NestedTraceLog2");
    PlatformThread::Sleep(TimeDelta::FromMilliseconds(100));
    NestedTraceLog1();
    PlatformThread::Sleep(TimeDelta::FromMilliseconds(100));
}
void NestedTraceLog3() {
    TRACE_EVENT0(EVENT_CATEGORIES, "NestedTraceLog3");
    PlatformThread::Sleep(TimeDelta::FromMilliseconds(100));
    NestedTraceLog2();
    PlatformThread::Sleep(TimeDelta::FromMilliseconds(100));
}
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    DemoTraceEventBegin();

    DemoLog();

    NestedTraceLog3();

    DemoTraceEventEnd();
    string dummy;
    cin >> dummy;
    return 0;
}
