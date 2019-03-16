#ifndef DISTRIBUTED_ID_H
#define DISTRIBUTED_ID_H

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#include <node.h>
#include <node_object_wrap.h>

class DistributedID : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> exports);

private:
	explicit DistributedID(int workId) {
		this->_workId = workId;
		this->EPOCH = initEpoc(2016, 10, 1);
		this->lastMilliseconds = 0;
		this->sequence = 0;
		this->sequenceOffset = 0;
	}
	
	~DistributedID() {
	}

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void generateId(const v8::FunctionCallbackInfo<v8::Value>& args);

	static v8::Persistent<v8::Function> constructor;

	static const std::chrono::system_clock::time_point initEpoc(int year, int month, int day) {
		struct tm ep_tm = {0};
		ep_tm.tm_year = year - 1900;
		ep_tm.tm_mon = month - 1;
		ep_tm.tm_mday = day;
		ep_tm.tm_isdst = 0;
		std::time_t ep_t = mktime(&ep_tm);
		return std::chrono::system_clock::from_time_t (ep_t);
	}

	unsigned long getNowMilliseconds() {
		return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - EPOCH).count();
	}

	unsigned long generateKey() {
		unsigned long currentMilliseconds = this->getNowMilliseconds();
		if (waitTolerateTimeDifferenceIfNeed(currentMilliseconds)) {
			currentMilliseconds = this->getNowMilliseconds();
		}
		// std::cout<<this->lastMilliseconds<<" "<<currentMilliseconds<<std::endl;
		if (this->lastMilliseconds == currentMilliseconds) {
			this->sequence = (this->sequence + 1) & SEQUENCE_MASK;
			if (0 == this->sequence) {
				currentMilliseconds = waitUntilNextTime(currentMilliseconds);
			}
		} else {
			vibrateSequenceOffset();
			this->sequence = this->sequenceOffset;
		}
		this->lastMilliseconds = currentMilliseconds;
		return (currentMilliseconds << TIMESTAMP_LEFT_SHIFT_BITS) | (this->_workId << WORKER_ID_LEFT_SHIFT_BITS) | this->sequence;
	}

	bool waitTolerateTimeDifferenceIfNeed(unsigned long currentMilliseconds) {
        if (this->lastMilliseconds <= currentMilliseconds) {
            return 0;
        }
        unsigned long timeDifferenceMilliseconds = lastMilliseconds - currentMilliseconds;
        if (timeDifferenceMilliseconds > maxTolerateTimeDifferenceMilliseconds) {
            std::cout << "Clock is moving backwards, " << currentMilliseconds << std::endl;
        }

		std::this_thread::sleep_for (std::chrono::milliseconds(timeDifferenceMilliseconds));

        return 1;
    }

    unsigned long waitUntilNextTime(unsigned long lastTime) {
        unsigned long result = getNowMilliseconds();
        while (result <= lastTime) {
            result = getNowMilliseconds();
        }
        return result;
    }

    void vibrateSequenceOffset() {
        sequenceOffset = 0xFF & (~sequenceOffset & 1);
    }

	unsigned long _workId;
	unsigned long sequence;
	unsigned long lastMilliseconds;
	unsigned char sequenceOffset;

	std::chrono::system_clock::time_point EPOCH;

	static const unsigned long maxTolerateTimeDifferenceMilliseconds = 10;
	static const int SEQUENCE_BITS = 12;
	static const int WORKER_ID_BITS = 10;
	static const unsigned long SEQUENCE_MASK = 0xFFF;
	static const int WORKER_ID_LEFT_SHIFT_BITS = 12;
	static const int TIMESTAMP_LEFT_SHIFT_BITS = WORKER_ID_LEFT_SHIFT_BITS + WORKER_ID_BITS;
	static const int WORKER_ID_MAX_VALUE = 1L << WORKER_ID_BITS;
};

#endif

