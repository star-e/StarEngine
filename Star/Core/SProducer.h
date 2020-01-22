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

#pragma once
#include <Star/Core/SConfig.h>
#include <Star/Core/SCoreTypes.h>

namespace Star::Core {

class Manager;
class Resource;

class STAR_CORE_API Producer {
public:
    Producer();
    Producer(const Producer&) = delete;
    Producer& operator=(const Producer&) = delete;
    virtual ~Producer() = 0;
protected:
    void deliver(const Resource& resource, void* pointer, bool async) const;
    void registerProducer(const ResourceType& tag);
private:
    friend class Manager;
    virtual bool load(const Resource& resource, bool async) = 0;
    virtual void created(const Resource& resource) = 0;
    virtual void destroy(const Resource& resource) noexcept = 0;
};

}
