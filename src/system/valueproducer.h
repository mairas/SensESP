#ifndef _value_producer_H_
#define _value_producer_H_

#include "observable.h"
#include <ArduinoJson.h>
#include "valueconsumer.h"

// SymmetricTransform is defined in transforms/transform.h
template <typename T> class SymmetricTransform;

/**
 * A ValueProducer<> is any device or piece of code that outputs a value for consumption
 * elsewhere.  They are Observable, allowing code to be notified whenever a new value
 * is available.  They can be connected directly to ValueConsumers of the same type
 * using the connectTo() method.
 */
template <typename T>
class ValueProducer : virtual public Observable {

    public:
        ValueProducer() {}


        /**
         * Returns the current value of this producer
         */
        virtual const T& get() { return output; }


        /**
         * Connects this producer to the specified consumer, registering that
         * consumer for notifications to when this producer's value changes
         * @param inputChannel Consumers can have one or more inputs feeding them
         *   This parameter allows you to specify which input number this producer
         *   is connecting to. For single input consumers, leave the index at
         *   zero.
         *  @see ValueConsumer::set_input()
         */
        void connectTo(ValueConsumer<T>* pConsumer, uint8_t inputChannel = 0) {
            this->attach([this, pConsumer, inputChannel](){
                pConsumer->set_input(this->get(), inputChannel);
            });
        }


        /**
         *  If the consumer this producer is connecting to is ALSO a producer
         *  of values of the same type, connectTo() calls can be chained
         *  together, as this specialized version returns the Producer/Consumer
         *  so this method can be called on THAT object.
         */
        SymmetricTransform<T>* connectTo(SymmetricTransform<T>* pProducerConsumer, uint8_t inputChannel = 0) {
            this->attach([this, pProducerConsumer, inputChannel](){
                pProducerConsumer->set_input(this->get(), inputChannel);
            });
            return pProducerConsumer;
        }

    protected:
        /**
         * The current value of this producer is stored here in this output member
         * (unless descendant classes override ValueProducer::get())
         */
        T output;
};

typedef ValueProducer<float> NumericProducer;
typedef ValueProducer<int>  IntegerProducer;
typedef ValueProducer<bool> BooleanProducer;
typedef ValueProducer<String> StringProducer;

#endif