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
                  `librarydb`.`books`.id_books, \n\
                  `librarydb`.`books`.name_book, \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`author`.author_record), \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`genre`.genre_record), \n\
                  `librarydb`.`bbk`.bbk_record, \n\
                  `librarydb`.`udc`.udc_record, \n\
                  `librarydb`.`books`.isbn, \n\
                  `librarydb`.`publisher`.publisher_record, \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`book_binding_type`.binding_type), \n\
                  `librarydb`.`books`.description_record \n\
        FROM \n\
                  `librarydb`.`books` \n\
                      JOIN \n\
                  `librarydb`.`author_join_table` ON `librarydb`.`author_join_table`.id_books = `librarydb`.`books`.id_books \n\
                      JOIN \n\
                  `librarydb`.`author` ON `librarydb`.`author`.id_author = `librarydb`.`author_join_table`.id_author \n\
                      JOIN \n\
                  `librarydb`.`genre_join_table` ON `librarydb`.`genre_join_table`.id_books = `librarydb`.`books`.id_books \n\
                      JOIN \n\
                  `librarydb`.`genre` ON `librarydb`.`genre`.id_genre = `librarydb`.`genre_join_table`.id_genre \n\
                      JOIN    \n\
                  `librarydb`.`book_binding_type` ON `librarydb`.`book_binding_type`.id_book_binding_type = `librarydb`.`books`.index_book_binding_type \n\
                      JOIN \n\
                  `librarydb`.`publisher` ON `librarydb`.`publisher`.id_publisher = `librarydb`.`books`.index_publisher \n\
                      JOIN \n\
                  `librarydb`.`udc` ON `librarydb`.`udc`.id_udc = `librarydb`.`books`.index_udc \n\
                      JOIN \n\
                  `librarydb`.`bbk` ON `librarydb`.`bbk`.id_bbk = `librarydb`.`books`.index_bbk \n\
        GROUP BY `librarydb`.`books`.id_books;";
        return query;
       }


    static QString search_by_genre_name_cache(QString genre_name){
        QString query =
        "SELECT * FROM `librarydb`.`cache` \
        WHERE `librarydb`.`cache`.id_books IN \
        (SELECT	librarydb.genre_join_table.id_books \
        FROM librarydb.genre_join_table \
        WHERE librarydb.genre_join_table.id_genre = \
        (SELECT	librarydb.genre.id_genre \
        FROM librarydb.genre \
        WHERE librarydb.genre.genre_record = '%1'));";
        return query.arg(genre_name);
    }

    static QString search_by_author_name_cache(QString author_name){
        QString query =
        "SELECT * FROM `librarydb`.`cache` \
        WHERE `librarydb`.`cache`.id_books IN (SELECT \
        librarydb.author_join_table.id_books FROM \
        librarydb.author_join_table WHERE \
        librarydb.author_join_table.id_author = (SELECT \
        librarydb.author.id_author FROM librarydb.author \
        WHERE librarydb.author.author_record = '%1'));";
        return query.arg(author_name);
    }

    static QString search_by_book_name_cache(QString book_name){
        QSqlQuery query;
        query.prepare("SELECT * FROM librarydb.cache WHERE librarydb.cache.name_book like ('%"+book_name+"%');");
        return query.lastQuery();
    }

    static QString search_by_id_book(qint32 id_book){
      QString query =
    "   SELECT \n\
                  `librarydb`.`books`.id_books, \n\
                  `librarydb`.`books`.name_book, \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`author`.author_record), \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`genre`.genre_record), \n\
                  `librarydb`.`bbk`.bbk_record, \n\
                  `librarydb`.`udc`.udc_record, \n\
                  `librarydb`.`books`.isbn, \n\
                  `librarydb`.`publisher`.publisher_record, \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`book_binding_type`.binding_type), \n\
                  `librarydb`.`books`.description_record \n\
        FROM \n\
                  `librarydb`.`books` \n\
                      JOIN \n\
                  `librarydb`.`author_join_table` ON `librarydb`.`author_join_table`.id_books = `librarydb`.`books`.id_books \n\
                      JOIN \n\
                  `librarydb`.`author` ON `librarydb`.`author`.id_author = `librarydb`.`author_join_table`.id_author \n\
                      JOIN \n\
                  `librarydb`.`genre_join_table` ON `librarydb`.`genre_join_table`.id_books = `librarydb`.`books`.id_books \n\
                      JOIN \n\
                  `librarydb`.`genre` ON `librarydb`.`genre`.id_genre = `librarydb`.`genre_join_table`.id_genre \n\
                      JOIN    \n\
                  `librarydb`.`book_binding_type` ON `librarydb`.`book_binding_type`.id_book_binding_type = `librarydb`.`books`.index_book_binding_type \n\
                      JOIN \n\
                  `librarydb`.`publisher` ON `librarydb`.`publisher`.id_publisher = `librarydb`.`books`.index_publisher \n\
                      JOIN \n\
                  `librarydb`.`udc` ON `librarydb`.`udc`.id_udc = `librarydb`.`books`.index_udc \n\
                      JOIN \n\
                  `librarydb`.`bbk` ON `librarydb`.`bbk`.id_bbk = `librarydb`.`books`.index_bbk \n\
        WHERE \n\
                   `librarydb`.`books`.id_books = '%1' \n\
        GROUP BY `librarydb`.`books`.id_books;";
        return query.arg(id_book);
       }

    static QString search_by_id_genre(qint32 id_book){
      QString query =
    "   SELECT \n\
                  `librarydb`.`books`.id_books, \n\
                  `librarydb`.`books`.name_book, \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`author`.author_record), \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`genre`.genre_record), \n\
                  `librarydb`.`bbk`.bbk_record, \n\
                  `librarydb`.`udc`.udc_record, \n\
                  `librarydb`.`books`.isbn, \n\
                  `librarydb`.`publisher`.publisher_record, \n\
                  GROUP_CONCAT(DISTINCT `librarydb`.`book_binding_type`.binding_type), \n\
                  `librarydb`.`books`.description_record \n\
        FROM \n\
                  `librarydb`.`books` \n\
                      JOIN \n\
                  `librarydb`.`author_join_table` ON `librarydb`.`author_join_table`.id_books = `librarydb`.`books`.id_books \n\
                      JOIN \n\
                  `librarydb`.`author` ON `librarydb`.`author`.id_author = `librarydb`.`author_join_table`.id_author \n\
                      JOIN \n\
                  `librarydb`.`genre_join_table` ON `librarydb`.`genre_join_table`.id_books = `librarydb`.`books`.id_books \n\
                      JOIN \n\
                  `librarydb`.`genre` ON `librarydb`.`genre`.id_genre = `librarydb`.`genre_join_table`.id_genre \n\
                      JOIN    \n\
                  `librarydb`.`book_binding_type` ON `librarydb`.`book_binding_type`.id_book_binding_type = `librarydb`.`books`.index_book_binding_type \n\
                      JOIN \n\
                  `librarydb`.`publisher` ON `librarydb`.`publisher`.id_publisher = `librarydb`.`books`.index_publisher \n\
                      JOIN \n\
                  `librarydb`.`udc` ON `librarydb`.`udc`.id_udc = `librarydb`.`books`.index_udc \n\
                      JOIN \n\
                  `librarydb`.`bbk` ON `librarydb`.`bbk`.id_bbk = `librarydb`.`books`.index_bbk \n\
              WHERE\n\
                  `librarydb`.`books`.id_books IN (SELECT \n\
                          librarydb.genre_join_table.id_books \n\
                      FROM \n\
                          librarydb.genre_join_table \n\
                      WHERE \n\
                          librarydb.genre_join_table.id_genre = '%1') \n\
        GROUP BY `librarydb`.`books`.id_books;";
        return query.arg(id_book);
       }

    static QString search_by_file_name(QString file_name){
    QString query =
    "   SELECT \n\
                `librarydb`.`filetables`.number_of_row \n\
        FROM\n\
                `librarydb`.`filetables` \n\
        WHERE \n\
                `librarydb`.`filetables`.file_name = '%1'";
    return query.arg(file_name);
    }

    static QString search_by_name_book(QString name_book){
        QString query =
        "SELECT `librarydb`.`books`.id_books \n\
        FROM \n\
            `librarydb`.`books` \n\
        WHERE \n\
            `librarydb`.`books`.name_book = '%1'";
        return query.arg(name_book);
    }

    static QString search_by_release_date_book(QString release_date_book){
        QString query =
            "SELECT * FROM librarydb.cache \
            WHERE librarydb.cache.release_date_book = '%1'";
        return query.arg(release_date_book);
    }
    static QString search_by_binding_book(QString name_binding){
        QString query =
        "SELECT `librarydb`.`book_binding_type`.id_book_binding_type \n\
        FROM \n\
            `librarydb`.`book_binding_type` \n\
        WHERE \n\
            `librarydb`.`book_binding_type`.`binding_type` = '%1'";
        return query.arg(name_binding);
    }

    static QString search_by_publisher_name(QString publisher_name){
        QString query =
        "SELECT `librarydb`.`publisher`.id_publisher \n\
        FROM \n\
            `librarydb`.`publisher` \n\
        WHERE \n\
            `librarydb`.`publisher`.`publisher_record` = '%1'";
        return query.arg(publisher_name);
    }

    static QString search_by_name_author(QString name_book){
        QString query =
        "SELECT `librarydb`.`author`.id_author \n\
        FROM \n\
            `librarydb`.`author` \n\
        WHERE \n\
            `librarydb`.`author`.author_record = '%1'";
        return query.arg(name_book);
    }

    static QString search_by_name_genre(QString name_genre){
        QString query =
        "SELECT `librarydb`.`genre`.id_genre \n\
        FROM  \n\
            `librarydb`.`genre`  \n\
        WHERE  \n\
            `librarydb`.`genre`.genre_record = '%1'";
        return query.arg(name_genre);
    }

    static QString delete_by_id_book(qint32 id_book){
        QString query =
        "DELETE FROM `librarydb`.`books` \n\
        WHERE \n\
            `librarydb`.`books`.id_books = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_author_join_table(qint32 id_book){
        QString query =
        "DELETE FROM `librarydb`.`author_join_table`\n\
        WHERE\n\
            `librarydb`.`author_join_table`.id_books = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_genre_join_table(qint32 id_book){
        QString query =
        "DELETE FROM `librarydb`.`genre_join_table`\n\
        WHERE\n\
            `librarydb`.`genre_join_table`.id_books = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_bbk(qint32 id_book){
        QString query =
        "DELETE FROM `librarydb`.`bbk` \n\
        WHERE \n\
            `librarydb`.`bbk`.id_bbk = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_udc(qint32 id_book){
        QString query =
        "DELETE FROM `librarydb`.`udc` \n\
        WHERE \n\
            `librarydb`.`udc`.id_udc = %1";
        return query.arg(id_book);
    }

    static QString delete_by_id_description(qint32 id_book){
        QString query =
        "DELETE FROM `librarydb`.`description` \n\
        WHERE \n\
            `librarydb`.`description`.id_description = %1";
        return query.arg(id_book);
    }

    static QString add_row_in_table_author(QString author_name){
        QString query = "INSERT INTO `librarydb`.`author`(`author_record`) VALUES ('%1');";
        return query.arg(author_name);
    }

    static QString add_row_in_table_genre(QString genre_name){
        QString query = "INSERT INTO `librarydb`.`genre`(`genre_record`) VALUES ('%1');";
        return query.arg(genre_name);
    }

    static QString add_row_in_table_publisher(QString publisher_name){
        QString query = "INSERT INTO `librarydb`.`publisher`(`publisher_record`) VALUES ('%1');";
        return query.arg(publisher_name);
    }

    static QString add_row_in_table_bbk(QString bbk_index){
        QString query = "INSERT INTO `librarydb`.`bbk`(`bbk_record`) VALUES ('%1');";
        return query.arg(bbk_index);
    }

    static QString add_row_in_table_udc(QString udc_index){
        QString query = "INSERT INTO `librarydb`.`udc`(`udc_record`) VALUES ('%1');";
        return query.arg(udc_index);
    }

    static QString add_row_in_table_description(QString description){
        QString query = "INSERT INTO `librarydb`.`description`(`description_record`) VALUES ('%1');";
        return query.arg(description);
    }

    static QString add_row_in_table_file_tables(QString file_name, qint32 number_of_row){
        QString query = "INSERT INTO `librarydb`.`filetables`(`file_name`, `number_of_row`) \n\
                         VALUES ('%1', %2);";
        return query.arg(file_name, number_of_row);
    }

    static QString update_row_in_table_file_tables(QString file_name, qint32 number_of_row){
        QString query = "UPDATE `librarydb`.`filetables` SET `number_of_row` = '%1' \n\
                         WHERE `file_name` = '%2';";
        return query.arg(file_name, number_of_row);
    }
/*
    static QString add_row_in_table_books(QString name_book, qint32 number_of_pages_book,
                               qint32 index_book_binding_type, qint32 release_date_book,
                               QString index_udc, QString index_bbk, qint32 index_publisher, QString isbn, QString description_record){
        QString query = "INSERT INTO `librarydb`.`books`\n\
                        (`name_book`,`number_of_pages_book`,\n\
                        `index_book_binding_type`,`release_date_book`,\n\
                        `index_udc`,`index_bbk`, `index_publisher`,`isbn`, `description_record`)\n\
                         VALUES ('%1', %2, %3, %4, %5, %6, %7, '%8', '%9');";
        return query.arg(name_book, number_of_pages_book, index_book_binding_type);
    }
*/
    static QString add_row_in_author_join_table(qint32 id_books, qint32 id_author){
        QString query = "INSERT INTO `librarydb`.`author_join_table` \n\
                        (`id_books`,`id_author`) \n\
                         VALUES (%1, %2);";
        return query.arg(id_books, id_author);
    }

    static QString add_row_in_genre_join_table(qint32 id_books, qint32 id_author){
        QString query = "INSERT INTO `librarydb`.`genre_join_table` \n\
                        (`id_books`,`id_genre`) \n\
                         VALUES (%s, %s);";
        return query.arg(id_books, id_author);
    }
};

#endif // QUERYFACTORY_H

