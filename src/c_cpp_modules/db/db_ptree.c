#include <stdio.h>;
#include "strbuf/strbuf.h";
#include "db_ptree.h";

TntDbFptreeNodeOffsetInDB db_ptree_insert(FILE *stream, strbuf path, TntDbFptreeNodeValue value){

};

TntDbFptreeNodeOffsetInDB db_ptree_getorcreate(FILE *stream, strbuf path){};
strbuf db_ptree_pathofoffset(FILE *stream, TntDbFptreeNodeOffsetInDB offset){

};

TntDbFptreeNodeOffsetInDB db_ptree_tree(FILE *stream, strbuf path_prefix){};

int DB_init(DBHandler dbHandler, FILE *dbFile, FILE *idbFile)
{
    /* TODO: Consider changing size of stream buffer to 1MB (enough for 2^16 units) */
    dbHandler.idb = dbFile;
    dbHandler.db = dbFile;
    return 0;
};

int DB_get(DBHandler dbhandler, DB_Key dbkey, void *buffer, size_t size)
{
    
    return 0;
};

