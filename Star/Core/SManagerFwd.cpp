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

#include "SManagerFwd.h"
#include "SManagerPrivate.h"

namespace Star::Core {

void Workflow::init(size_t resourceCount, size_t taskCount) {
    Manager::sInstance.reset(new Manager(resourceCount, taskCount));
}

STAR_CORE_API void Workflow::stop() noexcept {
    Expects(Manager::sInstance);
    Manager::sInstance->stop();
}

void Workflow::terminate() noexcept {
    Manager::sInstance.reset();
}

void Workflow::processEvents() {
    Expects(Manager::sInstance);
    Manager::sInstance->processEvents();
}

void Workflow::loadResources() {
    Expects(Manager::sInstance);
    Manager::sInstance->loadResources();
}

void Workflow::updateResources() {
    Expects(Manager::sInstance);
    Manager::sInstance->updateResources();
}

}
