#ifndef QUERYFACTORY_H
#define QUERYFACTORY_H
/*!
    @brief Query factory
    @brief Фабрика запросов
*/

#include <qstring.h>
#include <QSqlQuery>
#include <QVariant>

class QueryFactory
{
public:
    QueryFactory();

    static QString show_all(){
      QString query =
    "   SELECT \n\
                  `books`.id_books, \n\
                  `books`.name_book, \n\
                  GROUP_CONCAT(DISTINCT `author`.author_record), \n\
                  GROUP_CONCAT(DISTINCT `genre`.genre_record), \n\
                  `bbk`.bbk_record, \n\
                  `udc`.udc_record, \n\
                  `books`.isbn, \n\
                  `publisher`.publisher_record, \n\
                  GROUP_CONCAT(DISTINCT `book_binding_type`.binding_type), \n\
                  `books`.description_record \n\
        FROM \n\
                  `books` \n\
                      JOIN \n\
                  `author_join_table` ON `author_join_table`.id_books = `books`.id_books \n\
                      JOIN \n\
                  `author` ON `author`.id_author = `author_join_table`.id_author \n\
                      JOIN \n\
                  `genre_join_table` ON `genre_join_table`.id_books = `books`.id_books \n\
                      JOIN \n\
                  `genre` ON `genre`.id_genre = `genre_join_table`.id_genre \n\
                      JOIN    \n\
                  `book_binding_type` ON `book_binding_type`.id_book_binding_type = `books`.index_book_binding_type \n\
                      JOIN \n\
                  `publisher` ON `publisher`.id_publisher = `books`.index_publisher \n\
                      JOIN \n\
                  `udc` ON `udc`.id_udc = `books`.index_udc \n\
                      JOIN \n\
                  `bbk` ON `bbk`.id_bbk = `books`.index_bbk \n\
        GROUP BY `books`.id_books;";
        return query;
       }



    static QString search_by_genre_name_cache(QString genre_name){
        QString query =
        "SELECT * FROM `cache` \
        WHERE `cache`.id_books IN \
        (SELECT	genre_join_table.id_books \
        FROM genre_join_table \
        WHERE genre_join_table.id_genre = \
        (SELECT	genre.id_genre \
        FROM genre \
        WHERE genre.genre_record = '%1'));";
        return query.arg(genre_name);
    }

    static QString search_by_author_name_cache(QString author_name){
        QString query =
        "SELECT * FROM `cache` \
        WHERE `cache`.id_books IN (SELECT \
        author_join_table.id_books FROM \
        author_join_table WHERE \
        author_join_table.id_author = (SELECT \
        author.id_author FROM author \
        WHERE author.author_record = '%1'));";
        return query.arg(author_name);
    }

    static QString search_by_book_name_cache(QString book_name){
        QSqlQuery query;
        query.prepare("SELECT * FROM cache WHERE cache.name_book like ('%"+book_name+"%');");
        return query.lastQuery();
    }

    static QString search_by_name_publisher(QString name_publisher){
        QString query=
                "SELECT * FROM cache \
                WHERE cache.id_books IN (SELECT \
                id_books FROM books \
                WHERE books.index_publisher = (SELECT \
                id_publisher FROM \
                publisher WHERE publisher_record = '%1'));";
        return query.arg(name_publisher);
    }

    static QString search_by_ISBN(QString ISBN){
        QString query=
                "SELECT * FROM cache \
                WHERE cache.шisbn = '%1';";
        return query.arg(ISBN);
    }

    static QString search_by_udc(QString name){
        QString query=
                "SELECT * FROM cache \
                WHERE cache.id_books IN (SELECT \
                id_books FROM books \
                WHERE books.index_udc = (SELECT \
                id_udc FROM udc WHERE udc_record = '%1'));";
        return query.arg(name);
    }

    static QString search_by_bbk(QString name){
        QString query=
                "SELECT * FROM cache \
                WHERE cache.id_books IN (SELECT \
                id_books FROM books \
                WHERE books.index_bbk = (SELECT \
                id_bbk FROM bbk WHERE bbk_record = '%1'));";
        return query.arg(name);
    }

    static QString search_by_id_book(qint32 id_book){
      QString query =
    "   SELECT \n\
                  `books`.id_books, \n\
                  `books`.name_book, \n\
                  GROUP_CONCAT(DISTINCT `author`.author_record), \n\
                  GROUP_CONCAT(DISTINCT `genre`.genre_record), \n\
                  `bbk`.bbk_record, \n\
                  `udc`.udc_record, \n\
                  `books`.isbn, \n\
                  `publisher`.publisher_record, \n\
                  GROUP_CONCAT(DISTINCT `book_binding_type`.binding_type), \n\
                  `books`.description_record \n\
        FROM \n\
                  `books` \n\
                      JOIN \n\
                  `author_join_table` ON `author_join_table`.id_books = `books`.id_books \n\
                      JOIN \n\
                  `author` ON `author`.id_author = `author_join_table`.id_author \n\
                      JOIN \n\
                  `genre_join_table` ON `genre_join_table`.id_books = `books`.id_books \n\
                      JOIN \n\
                  `genre` ON `genre`.id_genre = `genre_join_table`.id_genre \n\
                      JOIN    \n\
                  `book_binding_type` ON `book_binding_type`.id_book_binding_type = `books`.index_book_binding_type \n\
                      JOIN \n\
                  `publisher` ON `publisher`.id_publisher = `books`.index_publisher \n\
                      JOIN \n\
                  `udc` ON `udc`.id_udc = `books`.index_udc \n\
                      JOIN \n\
                  `bbk` ON `bbk`.id_bbk = `books`.index_bbk \n\
        WHERE \n\
                   `books`.id_books = '%1' \n\
        GROUP BY `books`.id_books;";
        return query.arg(id_book);
       }

    static QString search_by_id_genre(qint32 id_book){
      QString query =
    "   SELECT \n\
                  `books`.id_books, \n\
                  `books`.name_book, \n\
                  GROUP_CONCAT(DISTINCT `author`.author_record), \n\
                  GROUP_CONCAT(DISTINCT `genre`.genre_record), \n\
                  `bbk`.bbk_record, \n\
                  `udc`.udc_record, \n\
                  `books`.isbn, \n\
                  `publisher`.publisher_record, \n\
                  GROUP_CONCAT(DISTINCT `book_binding_type`.binding_type), \n\
                  `books`.description_record \n\
        FROM \n\
                  `books` \n\
                      JOIN \n\
                  `author_join_table` ON `author_join_table`.id_books = `books`.id_books \n\
                      JOIN \n\
                  `author` ON `author`.id_author = `author_join_table`.id_author \n\
                      JOIN \n\
                  `genre_join_table` ON `genre_join_table`.id_books = `books`.id_books \n\
                      JOIN \n\
                  `genre` ON `genre`.id_genre = `genre_join_table`.id_genre \n\
                      JOIN    \n\
                  `book_binding_type` ON `book_binding_type`.id_book_binding_type = `books`.index_book_binding_type \n\
                      JOIN \n\
                  `publisher` ON `publisher`.id_publisher = `books`.index_publisher \n\
                      JOIN \n\
                  `udc` ON `udc`.id_udc = `books`.index_udc \n\
                      JOIN \n\
                  `bbk` ON `bbk`.id_bbk = `books`.index_bbk \n\
              WHERE\n\
                  `books`.id_books IN (SELECT \n\
                          genre_join_table.id_books \n\
                      FROM \n\
                          genre_join_table \n\
                      WHERE \n\
                          genre_join_table.id_genre = '%1') \n\
        GROUP BY `books`.id_books;";
        return query.arg(id_book);
       }

    static QString search_by_file_name(QString file_name){
    QString query =
    "   SELECT \n\
                `filetables`.number_of_row \n\
        FROM\n\
                `filetables` \n\
        WHERE \n\
                `filetables`.file_name = '%1'";
    return query.arg(file_name);
    }

    static QString search_by_name_book(QString name_book){
        QString query =
        "SELECT `books`.id_books \n\
        FROM \n\
            `books` \n\
        WHERE \n\
            `books`.name_book = '%1'";
        return query.arg(name_book);
    }

    static QString search_by_release_date_book(QString release_date_book){
        QString query =
            "SELECT * FROM cache \
            WHERE cache.release_date_book = '%1'";
        return query.arg(release_date_book);
    }
    static QString search_by_binding_book(QString name_binding){
        QString query =
        "SELECT `book_binding_type`.id_book_binding_type \n\
        FROM \n\
            `book_binding_type` \n\
        WHERE \n\
            `book_binding_type`.`binding_type` = '%1'";
        return query.arg(name_binding);
    }

    static QString search_by_publisher_name(QString publisher_name){
        QString query =
        "SELECT `publisher`.id_publisher \n\
        FROM \n\
            `publisher` \n\
        WHERE \n\
            `publisher`.`publisher_record` = '%1'";
        return query.arg(publisher_name);
    }

    static QString search_by_name_author(QString name_book){
        QString query =
        "SELECT `author`.id_author \n\
        FROM \n\
            `author` \n\
        WHERE \n\
            `author`.author_record = '%1'";
        return query.arg(name_book);
    }

    static QString search_by_name_genre(QString name_genre){
        QString query =
        "SELECT `genre`.id_genre \n\
        FROM  \n\
            `genre`  \n\
        WHERE  \n\
            `genre`.genre_record = '%1'";
        return query.arg(name_genre);
    }

    static QString delete_by_id_book(qint32 id_book){
        QString query =
        "DELETE FROM `books` \n\
        WHERE \n\
            `books`.id_books = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_author_join_table(qint32 id_book){
        QString query =
        "DELETE FROM `author_join_table`\n\
        WHERE\n\
            `author_join_table`.id_books = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_genre_join_table(qint32 id_book){
        QString query =
        "DELETE FROM `genre_join_table`\n\
        WHERE\n\
            `genre_join_table`.id_books = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_bbk(qint32 id_book){
        QString query =
        "DELETE FROM `bbk` \n\
        WHERE \n\
            `bbk`.id_bbk = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_udc(qint32 id_book){
        QString query =
        "DELETE FROM `udc` \n\
        WHERE \n\
            `udc`.id_udc = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_description(qint32 id_book){
        QString query =
        "DELETE FROM `description` \n\
        WHERE \n\
            `description`.id_description = %1";
        return query.arg(id_book);
    }

    static QString add_row_in_table_author(QString author_name){
        QString query = "INSERT INTO `author`(`author_record`) VALUES ('%1');";
        return query.arg(author_name);
    }

    static QString add_row_in_table_genre(QString genre_name){
        QString query = "INSERT INTO `genre`(`genre_record`) VALUES ('%1');";
        return query.arg(genre_name);
    }

    static QString add_row_in_table_publisher(QString publisher_name){
        QString query = "INSERT INTO `publisher`(`publisher_record`) VALUES ('%1');";
        return query.arg(publisher_name);
    }

    static QString add_row_in_table_bbk(QString bbk_index){
        QString query = "INSERT INTO `bbk`(`bbk_record`) VALUES ('%1');";
        return query.arg(bbk_index);
    }

    static QString add_row_in_table_udc(QString udc_index){
        QString query = "INSERT INTO `udc`(`udc_record`) VALUES ('%1');";
        return query.arg(udc_index);
    }

    static QString add_row_in_table_description(QString description){
        QString query = "INSERT INTO `description`(`description_record`) VALUES ('%1');";
        return query.arg(description);
    }

    static QString add_row_in_table_file_tables(QString file_name, qint32 number_of_row){
        QString query = "INSERT INTO `filetables`(`file_name`, `number_of_row`) \n\
                         VALUES ('%1', %2);";
        return query.arg(file_name, number_of_row);
    }

    static QString update_row_in_table_file_tables(QString file_name, qint32 number_of_row){
        QString query = "UPDATE `filetables` SET `number_of_row` = '%1' \n\
                         WHERE `file_name` = '%2';";
        return query.arg(file_name, number_of_row);
    }
/*
    static QString add_row_in_table_books(QString name_book, qint32 number_of_pages_book,
                               qint32 index_book_binding_type, qint32 release_date_book,
                               QString index_udc, QString index_bbk, qint32 index_publisher, QString isbn, QString description_record){
        QString query = "INSERT INTO `books`\n\
                        (`name_book`,`number_of_pages_book`,\n\
                        `index_book_binding_type`,`release_date_book`,\n\
                        `index_udc`,`index_bbk`, `index_publisher`,`isbn`, `description_record`)\n\
                         VALUES ('%1', %2, %3, %4, %5, %6, %7, '%8', '%9');";
        return query.arg(name_book, number_of_pages_book, index_book_binding_type);
    }
*/
    static QString add_row_in_author_join_table(qint32 id_books, qint32 id_author){
        QString query = "INSERT INTO `author_join_table` \n\
                        (`id_books`,`id_author`) \n\
                         VALUES (%1, %2);";
        return query.arg(id_books, id_author);
    }

    static QString add_row_in_genre_join_table(qint32 id_books, qint32 id_author){
        QString query = "INSERT INTO `genre_join_table` \n\
                        (`id_books`,`id_genre`) \n\
                         VALUES (%s, %s);";
        return query.arg(id_books, id_author);
    }
};

#endif // QUERYFACTORY_H

