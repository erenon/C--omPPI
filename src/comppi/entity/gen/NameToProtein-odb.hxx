// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef COMPPI_ENTITY_GEN_NAME_TO_PROTEIN_ODB_HXX
#define COMPPI_ENTITY_GEN_NAME_TO_PROTEIN_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20200UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include <comppi/entity/NameToProtein.h>

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/prepared-query.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // NameToProtein
  //
  template <>
  struct class_traits< ::comppi::entity::NameToProtein >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::comppi::entity::NameToProtein >
  {
    public:
    typedef ::comppi::entity::NameToProtein object_type;
    typedef ::comppi::entity::NameToProtein* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef unsigned int id_type;

    static const bool auto_id = true;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_op_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/mysql/version.hxx>
#include <odb/mysql/forward.hxx>
#include <odb/mysql/binding.hxx>
#include <odb/mysql/mysql-types.hxx>
#include <odb/mysql/query.hxx>

namespace odb
{
  // NameToProtein
  //
  template <typename A>
  struct pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >
  {
    // id
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        unsigned int,
        mysql::id_ulong >::query_type,
      mysql::id_ulong >
    id_type_;

    static const id_type_ id;

    // specieId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        int,
        mysql::id_long >::query_type,
      mysql::id_long >
    specieId_type_;

    static const specieId_type_ specieId;

    // name
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    name_type_;

    static const name_type_ name;

    // namingConvention
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    namingConvention_type_;

    static const namingConvention_type_ namingConvention;

    // protein
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        unsigned int,
        mysql::id_ulong >::query_type,
      mysql::id_ulong >
    protein_type_;

    static const protein_type_ protein;
  };

  template <typename A>
  const typename pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::id_type_
  pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  id (A::table_name, "`id`", 0);

  template <typename A>
  const typename pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::specieId_type_
  pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  specieId (A::table_name, "`specieId`", 0);

  template <typename A>
  const typename pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::name_type_
  pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  name (A::table_name, "`name`", 0);

  template <typename A>
  const typename pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::namingConvention_type_
  pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  namingConvention (A::table_name, "`namingConvention`", 0);

  template <typename A>
  const typename pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::protein_type_
  pointer_query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  protein (A::table_name, "`proteinId`", 0);

  template <>
  class access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >:
    public access::object_traits< ::comppi::entity::NameToProtein >
  {
    public:
    struct id_image_type
    {
      unsigned int id_value;
      my_bool id_null;

      std::size_t version;
    };

    struct image_type
    {
      // _id
      //
      unsigned int _id_value;
      my_bool _id_null;

      // _specieId
      //
      int _specieId_value;
      my_bool _specieId_null;

      // _name
      //
      details::buffer _name_value;
      unsigned long _name_size;
      my_bool _name_null;

      // _namingConvention
      //
      details::buffer _namingConvention_value;
      unsigned long _namingConvention_size;
      my_bool _namingConvention_null;

      // _protein
      //
      unsigned int _protein_value;
      my_bool _protein_null;

      std::size_t version;
    };

    struct protein_tag;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&, my_bool*);

    static void
    bind (MYSQL_BIND*,
          image_type&,
          mysql::statement_kind);

    static void
    bind (MYSQL_BIND*, id_image_type&);

    static bool
    init (image_type&, const object_type&, mysql::statement_kind);

    static void
    init (object_type&, const image_type&, database*);

    static void
    init (id_image_type&, const id_type&);

    typedef mysql::object_statements<object_type> statements_type;

    typedef mysql::query_base query_base_type;

    struct container_statement_cache_type;

    static const std::size_t column_count = 5UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, object_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static odb::details::shared_ptr<prepared_query_impl>
    prepare_query (connection&, const char*, const query_base_type&);

    static odb::details::shared_ptr<result_impl>
    execute_query (prepared_query_impl&);

    public:
    static bool
    find_ (statements_type&, const id_type*);

    static void
    load_ (statements_type&, object_type&);
  };

  template <>
  class access::object_traits_impl< ::comppi::entity::NameToProtein, id_common >:
    public access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >
  {
  };

  // NameToProtein
  //
  template <>
  struct alias_traits<
    ::comppi::entity::Protein,
    id_mysql,
    access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::protein_tag>
  {
    static const char table_name[];
  };

  template <>
  struct query_columns_base< ::comppi::entity::NameToProtein, id_mysql >
  {
    // protein
    //
    typedef
    odb::alias_traits<
      ::comppi::entity::Protein,
      id_mysql,
      access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::protein_tag>
    protein_alias_;
  };

  template <typename A>
  struct query_columns< ::comppi::entity::NameToProtein, id_mysql, A >:
    query_columns_base< ::comppi::entity::NameToProtein, id_mysql >
  {
    // id
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        unsigned int,
        mysql::id_ulong >::query_type,
      mysql::id_ulong >
    id_type_;

    static const id_type_ id;

    // specieId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        int,
        mysql::id_long >::query_type,
      mysql::id_long >
    specieId_type_;

    static const specieId_type_ specieId;

    // name
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    name_type_;

    static const name_type_ name;

    // namingConvention
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    namingConvention_type_;

    static const namingConvention_type_ namingConvention;

    // protein
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        unsigned int,
        mysql::id_ulong >::query_type,
      mysql::id_ulong >
    protein_column_type_;

    typedef
    odb::query_pointer<
      odb::pointer_query_columns<
        ::comppi::entity::Protein,
        id_mysql,
        protein_alias_ > >
    protein_pointer_type_;

    struct protein_type_: protein_pointer_type_, protein_column_type_
    {
      protein_type_ (const char* t, const char* c, const char* conv)
        : protein_column_type_ (t, c, conv)
      {
      }
    };

    static const protein_type_ protein;
  };

  template <typename A>
  const typename query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::id_type_
  query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  id (A::table_name, "`id`", 0);

  template <typename A>
  const typename query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::specieId_type_
  query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  specieId (A::table_name, "`specieId`", 0);

  template <typename A>
  const typename query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::name_type_
  query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  name (A::table_name, "`name`", 0);

  template <typename A>
  const typename query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::namingConvention_type_
  query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  namingConvention (A::table_name, "`namingConvention`", 0);

  template <typename A>
  const typename query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::protein_type_
  query_columns< ::comppi::entity::NameToProtein, id_mysql, A >::
  protein (A::table_name, "`proteinId`", 0);
}

#include <comppi/entity/gen/NameToProtein-odb.ixx>

#include <odb/post.hxx>

#endif // COMPPI_ENTITY_GEN_NAME_TO_PROTEIN_ODB_HXX