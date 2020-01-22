// Copyright (C) 2019-2020 star.engine at outlook dot com
//
// This file is part of StarEngine
//
// StarEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// StarEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with StarEngine.  If not, see <https://www.gnu.org/licenses/>.

#include "SResource.h"
#include "SManagerPrivate.h"

namespace Star::Core {

bool ControlBlock::try_send(const EventTryStart& e) noexcept {
    return Manager::instance().try_send(*static_cast<Resource*>(this), e.mAsync);
}

void ControlBlock::unloaded_queued(const EventLoad& e) {
    Manager::instance().enqueue(*static_cast<Resource*>(this), e.mAsync);
}

void ControlBlock::queued_unloaded(const EventUnload& e) noexcept {
    Manager::instance().dequeue(*static_cast<Resource*>(this), e.mAsync);
}

void ControlBlock::loading_loaded(const EventCreated& e) {
    mPointer = e.mPointer;
    Manager::instance().finishLoadingSucceeded(*static_cast<Resource*>(this));
}

void ControlBlock::cancelling_unloaded(const EventCreated& e) noexcept {
    mPointer = nullptr;
    Manager::instance().finishLoadingFailed(*static_cast<Resource*>(this));
}

void ControlBlock::loaded_unloaded(const EventUnload& e) noexcept {
    mPointer = nullptr;
    Manager::instance().destroy(*static_cast<Resource*>(this));
}

void Resource::loadNow() noexcept {
    Manager::instance().loadNow(*static_cast<Resource*>(this));
}

void Resource::startLoading() const noexcept {
    Manager::instance().postLoad(*const_cast<Resource*>(this));
}

void Resource::startUnloading() const noexcept {
    Manager::instance().postUnload(*const_cast<Resource*>(this));
}

}
