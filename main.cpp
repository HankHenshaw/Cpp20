#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string_view>
#include <forward_list>
#include <deque>
#include "concepts.h"
#include "ranges.h"
#include "coroutines.h"
#include "others.h"

int main()
{
    conceptExamples();
    rangesExamples();
    genUse();
    othersExamples();

    return 0;
}