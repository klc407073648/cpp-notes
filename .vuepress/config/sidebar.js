let {
    genSidebar4Cplusplus, genSidebar4Database, genSidebar4Alg, genSidebar4Program, genSidebar4develop, genSidebar4microServices,
    genSidebar4method, genSidebar4Devops, genSidebar4project, genSidebar4booknote, genSidebar4interview, genSidebar4Article,
    genSidebar4dailyUse, genSidebar4About, genSidebar4Grow, genSidebar4Vue
} = require('./function.js')

module.exports = {
    "/md/c++/": genSidebar4Cplusplus(),
    "/md/database/": genSidebar4Database(),
    "/md/algorithm/": genSidebar4Alg(),
    "/md/programming/": genSidebar4Program(),
    "/md/develop/": genSidebar4develop(),
    "/md/micro-services/": genSidebar4microServices(),
    // "/md/arch/": genSidebar4arch(),
    "/md/method/": genSidebar4method(),
    "/md/devops/": genSidebar4Devops(),
    "/md/project/": genSidebar4project(),
    "/md/book-note/": genSidebar4booknote(),
    "/md/interview/": genSidebar4interview(),
    "/md/article/": genSidebar4Article(),
    "/md/daily-use/": genSidebar4dailyUse(),
    "/md/about/": genSidebar4About(),
    "/md/grow/": genSidebar4Grow(),
    "/md/vue/": genSidebar4Vue(),
}