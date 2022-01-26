//
//  PubSub.cpp
//  SDLSkeleton
//
//  Created by James Folk on 2/22/20.
//

#include "PubSub.h"

Publisher::Publisher() : mNotifyEnabled(true) {}

Publisher::~Publisher() {}

void Publisher::subscribe(Subscriber *s) { mSubscribers.push_back(s); }

void Publisher::unsubscribe(Subscriber *s) { mSubscribers.remove(s); }

void Publisher::notify(void *what, Subscriber *s) {

    if (mNotifyEnabled) {

        std::list<Subscriber *>::iterator p;

        for (p = mSubscribers.begin(); p != mSubscribers.end(); p++)
            if (*p != s)
                (*p)->update(this, what);
    }
    mNotifyEnabled = true;
}

void Publisher::setNotifyEnabled(bool flag) { mNotifyEnabled = flag; }

bool Publisher::getNotifyEnabled() const { return mNotifyEnabled; }
