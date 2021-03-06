/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 * ALPS Project: Algorithms and Libraries for Physics Simulations                  *
 *                                                                                 *
 * ALPS Libraries                                                                  *
 *                                                                                 *
 * Copyright (C) 2010 - 2011 by Lukas Gamper <gamperl@gmail.com>                   *
 *                                                                                 *
 * This software is part of the ALPS libraries, published under the ALPS           *
 * Library License; you can use, redistribute it and/or modify it under            *
 * the terms of the license, either version 1 or (at your option) any later        *
 * version.                                                                        *
 *                                                                                 *
 * You should have received a copy of the ALPS Library License along with          *
 * the ALPS Libraries; see the file LICENSE.txt. If not, the license is also       *
 * available from http://alps.comp-phys.org/.                                      *
 *                                                                                 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT       *
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE       *
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,     *
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER     *
 * DEALINGS IN THE SOFTWARE.                                                       *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <alps/hdf5/archive.hpp>

#include <boost/filesystem.hpp>
#include <boost/random.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    std::string const filename = "test%05d.h5";
    if (boost::filesystem::exists(boost::filesystem::path(filename)))
        boost::filesystem::remove(boost::filesystem::path(filename));
    {
        using namespace alps;
        alps::hdf5::archive oar(filename, "al");
    }
    {
        using namespace alps;
        alps::hdf5::archive oar(filename, "al");
        oar << make_pvp("/data", 42);
    }
    {
        using namespace alps;
        alps::hdf5::archive iar(filename, "l");
        int test;
        iar >> make_pvp("/data", test);
        {
            alps::hdf5::archive iar2(filename, "l");
            int test2;
            iar2 >> make_pvp("/data", test2);
            iar >> make_pvp("/data", test);
        }
        iar >> make_pvp("/data", test);
        {
            alps::hdf5::archive iar3(filename, "l");
            int test3;
            iar >> make_pvp("/data", test);
            iar3 >> make_pvp("/data", test3);
        }
        iar >> make_pvp("/data", test);
    }
    {
        using namespace alps;
        alps::hdf5::archive iar4(filename, "l");
        int test4;
        iar4 >> make_pvp("/data", test4);
    }
    boost::filesystem::remove(boost::filesystem::path(filename));
    return 0;
}
