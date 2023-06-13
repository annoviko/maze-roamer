#pragma once


#include <variant>

#include "quest_collect.h"
#include "quest_kill.h"
#include "quest_reach_checkpoint.h"


using quest = std::variant <
    quest_collect,
    quest_kill,
    quest_reach_checkpoint
>;
