//
//  PubSub.hpp
//  SDLSkeleton
//
//  Created by James Folk on 2/22/20.
//

#ifndef PubSub_hpp
#define PubSub_hpp

#include <list>
class Publisher;

class Subscriber {
  public:
    virtual ~Subscriber() {}
    virtual void update(Publisher *who, void *userdata = 0) = 0;
};

class Publisher {
    Publisher(const Publisher &) = delete;
    const Publisher &operator=(const Publisher &) = delete;

  public:
    Publisher();
    virtual ~Publisher();

    void subscribe(Subscriber *s);
    void unsubscribe(Subscriber *s);

    void notify(void *what = 0, Subscriber *s = 0);

    void setNotifyEnabled(bool flag);
    bool getNotifyEnabled() const;

  private:
    std::list<Subscriber *> mSubscribers;
    bool mNotifyEnabled;
};

#endif /* PubSub_hpp */
