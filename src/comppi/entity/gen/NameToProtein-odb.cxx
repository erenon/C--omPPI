// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include <comppi/entity/gen/NameToProtein-odb.hxx>
#include <comppi/entity/gen/Protein-odb.hxx>

#include <cassert>
#include <cstring>  // std::memcpy


#include <odb/mysql/traits.hxx>
#include <odb/mysql/database.hxx>
#include <odb/mysql/transaction.hxx>
#include <odb/mysql/connection.hxx>
#include <odb/mysql/statement.hxx>
#include <odb/mysql/statement-cache.hxx>
#include <odb/mysql/simple-object-statements.hxx>
#include <odb/mysql/container-statements.hxx>
#include <odb/mysql/exceptions.hxx>
#include <odb/mysql/prepared-query.hxx>
#include <odb/mysql/simple-object-result.hxx>
#include <odb/mysql/enum.hxx>

namespace odb
{
  // NameToProtein
  //

  const char alias_traits<  ::comppi::entity::Protein,
    id_mysql,
    access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::protein_tag>::
  table_name[] = "`proteinId`";

  access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::id_type
  access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  id (const image_type& i)
  {
    mysql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_value (
        id,
        i._id_value,
        i._id_null);
    }

    return id;
  }

  bool access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  grow (image_type& i, my_bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // _id
    //
    t[0UL] = 0;

    // _specieId
    //
    t[1UL] = 0;

    // _name
    //
    if (t[2UL])
    {
      i._name_value.capacity (i._name_size);
      grew = true;
    }

    // _namingConvention
    //
    if (t[3UL])
    {
      i._namingConvention_value.capacity (i._namingConvention_size);
      grew = true;
    }

    // _protein
    //
    t[4UL] = 0;

    return grew;
  }

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  bind (MYSQL_BIND* b,
        image_type& i,
        mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    std::size_t n (0);

    // _id
    //
    if (sk != statement_update)
    {
      b[n].buffer_type = MYSQL_TYPE_LONG;
      b[n].is_unsigned = 1;
      b[n].buffer = &i._id_value;
      b[n].is_null = &i._id_null;
      n++;
    }

    // _specieId
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 0;
    b[n].buffer = &i._specieId_value;
    b[n].is_null = &i._specieId_null;
    n++;

    // _name
    //
    b[n].buffer_type = MYSQL_TYPE_STRING;
    b[n].buffer = i._name_value.data ();
    b[n].buffer_length = static_cast<unsigned long> (
      i._name_value.capacity ());
    b[n].length = &i._name_size;
    b[n].is_null = &i._name_null;
    n++;

    // _namingConvention
    //
    b[n].buffer_type = MYSQL_TYPE_STRING;
    b[n].buffer = i._namingConvention_value.data ();
    b[n].buffer_length = static_cast<unsigned long> (
      i._namingConvention_value.capacity ());
    b[n].length = &i._namingConvention_size;
    b[n].is_null = &i._namingConvention_null;
    n++;

    // _protein
    //
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i._protein_value;
    b[n].is_null = &i._protein_null;
    n++;
  }

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  bind (MYSQL_BIND* b, id_image_type& i)
  {
    std::size_t n (0);
    b[n].buffer_type = MYSQL_TYPE_LONG;
    b[n].is_unsigned = 1;
    b[n].buffer = &i.id_value;
    b[n].is_null = &i.id_null;
  }

  bool access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  init (image_type& i, const object_type& o, mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    bool grew (false);

    // _id
    //
    if (sk == statement_insert)
    {
      unsigned int const& v =
        o._id;

      bool is_null (false);
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_image (
        i._id_value, is_null, v);
      i._id_null = is_null;
    }

    // _specieId
    //
    {
      int const& v =
        o._specieId;

      bool is_null (false);
      mysql::value_traits<
          int,
          mysql::id_long >::set_image (
        i._specieId_value, is_null, v);
      i._specieId_null = is_null;
    }

    // _name
    //
    {
      ::std::string const& v =
        o._name;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i._name_value.capacity ());
      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_image (
        i._name_value,
        size,
        is_null,
        v);
      i._name_null = is_null;
      i._name_size = static_cast<unsigned long> (size);
      grew = grew || (cap != i._name_value.capacity ());
    }

    // _namingConvention
    //
    {
      ::std::string const& v =
        o._namingConvention;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i._namingConvention_value.capacity ());
      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_image (
        i._namingConvention_value,
        size,
        is_null,
        v);
      i._namingConvention_null = is_null;
      i._namingConvention_size = static_cast<unsigned long> (size);
      grew = grew || (cap != i._namingConvention_value.capacity ());
    }

    // _protein
    //
    {
      ::std::shared_ptr< ::comppi::entity::Protein > const& v =
        o._protein;

      typedef object_traits< ::comppi::entity::Protein > obj_traits;
      typedef odb::pointer_traits< ::std::shared_ptr< ::comppi::entity::Protein > > ptr_traits;

      bool is_null (ptr_traits::null_ptr (v));
      if (!is_null)
      {
        const obj_traits::id_type& id (
          obj_traits::id (ptr_traits::get_ref (v)));

        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_image (
          i._protein_value, is_null, id);
        i._protein_null = is_null;
      }
      else
        i._protein_null = 1;
    }

    return grew;
  }

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  init (object_type& o, const image_type& i, database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // _id
    //
    {
      unsigned int& v =
        o._id;

      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_value (
        v,
        i._id_value,
        i._id_null);
    }

    // _specieId
    //
    {
      int& v =
        o._specieId;

      mysql::value_traits<
          int,
          mysql::id_long >::set_value (
        v,
        i._specieId_value,
        i._specieId_null);
    }

    // _name
    //
    {
      ::std::string& v =
        o._name;

      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_value (
        v,
        i._name_value,
        i._name_size,
        i._name_null);
    }

    // _namingConvention
    //
    {
      ::std::string& v =
        o._namingConvention;

      mysql::value_traits<
          ::std::string,
          mysql::id_string >::set_value (
        v,
        i._namingConvention_value,
        i._namingConvention_size,
        i._namingConvention_null);
    }

    // _protein
    //
    {
      ::std::shared_ptr< ::comppi::entity::Protein >& v =
        o._protein;

      typedef object_traits< ::comppi::entity::Protein > obj_traits;
      typedef odb::pointer_traits< ::std::shared_ptr< ::comppi::entity::Protein > > ptr_traits;

      if (i._protein_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        mysql::value_traits<
            obj_traits::id_type,
            mysql::id_ulong >::set_value (
          id,
          i._protein_value,
          i._protein_null);

        // If a compiler error points to the line below, then
        // it most likely means that a pointer used in a member
        // cannot be initialized from an object pointer.
        //
        v = ptr_traits::pointer_type (
          static_cast<mysql::database*> (db)->load<
            obj_traits::object_type > (id));
      }
    }
  }

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  init (id_image_type& i, const id_type& id)
  {
    {
      bool is_null (false);
      mysql::value_traits<
          unsigned int,
          mysql::id_ulong >::set_image (
        i.id_value, is_null, id);
      i.id_null = is_null;
    }
  }

  struct access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::container_statement_cache_type
  {
    container_statement_cache_type (
      mysql::connection&,
      mysql::binding&)
    {
    }
  };

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::persist_statement[] =
  "INSERT INTO `NameToProtein` ("
  "`id`,"
  "`specieId`,"
  "`name`,"
  "`namingConvention`,"
  "`proteinId`)"
  " VALUES (?,?,?,?,?)";

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::find_statement[] =
  "SELECT "
  "`NameToProtein`.`id`,"
  "`NameToProtein`.`specieId`,"
  "`NameToProtein`.`name`,"
  "`NameToProtein`.`namingConvention`,"
  "`NameToProtein`.`proteinId`"
  " FROM `NameToProtein`"
  " WHERE `NameToProtein`.`id`=?";

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::update_statement[] =
  "UPDATE `NameToProtein` SET "
  "`specieId`=?,"
  "`name`=?,"
  "`namingConvention`=?,"
  "`proteinId`=?"
  " WHERE `id`=?";

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::erase_statement[] =
  "DELETE FROM `NameToProtein`"
  " WHERE `id`=?";

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::query_statement[] =
  "SELECT "
  "`NameToProtein`.`id`,"
  "`NameToProtein`.`specieId`,"
  "`NameToProtein`.`name`,"
  "`NameToProtein`.`namingConvention`,"
  "`NameToProtein`.`proteinId`"
  " FROM `NameToProtein`"
  " LEFT JOIN `Protein` AS `proteinId` ON `proteinId`.`id`=`NameToProtein`.`proteinId`"
  " ";

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::erase_query_statement[] =
  "DELETE FROM `NameToProtein`"
  " ";

  const char access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::table_name[] =
  "`NameToProtein`";

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  persist (database& db, object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    im._id_value = 0;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    obj._id = static_cast< id_type > (st.id ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace mysql;

    callback (db, obj, callback_event::pre_update);

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, obj._id);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (i.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, i);
        sts.id_image_version (i.version);
        idb.version++;
      }

      sts.update_id_image_version (i.version);

      if (!u)
        imb.version++;
    }

    if (sts.update_statement ().execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  erase (database& db, const id_type& id)
  {
    using namespace mysql;

    ODB_POTENTIALLY_UNUSED (db);

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  bool access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj);
    sts.load_delayed ();
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  reload (database& db, object_type& obj)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    const id_type& id  (
      obj._id);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj);
    sts.load_delayed ();
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  find_ (statements_type& sts, const id_type* id)
  {
    using namespace mysql;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());
    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  result< access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::object_type >
  access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  query (database&, const query_base_type& q)
  {
    using namespace mysql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        query_statement + q.clause (),
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) mysql::object_result_impl<object_type> (
        q, st, sts));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace mysql;

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    q.init_parameters ();
    delete_statement st (
      conn,
      erase_query_statement + q.clause (),
      q.parameters_binding ());

    return st.execute ();
  }

  odb::details::shared_ptr<prepared_query_impl>
  access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  prepare_query (connection& c, const char* n, const query_base_type& q)
  {
    using namespace mysql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mysql::connection& conn (
      static_cast<mysql::connection&> (c));

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    shared_ptr<mysql::prepared_query_impl> r (
      new (shared) mysql::prepared_query_impl (conn));
    r->name = n;
    r->execute = &execute_query;
    r->query = q;
    r->stmt.reset (
      new (shared) select_statement (
        conn,
        query_statement + r->query.clause (),
        r->query.parameters_binding (),
        imb));

    return r;
  }

  odb::details::shared_ptr<result_impl>
  access::object_traits_impl< ::comppi::entity::NameToProtein, id_mysql >::
  execute_query (prepared_query_impl& q)
  {
    using namespace mysql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mysql::prepared_query_impl& pq (
      static_cast<mysql::prepared_query_impl&> (q));
    shared_ptr<select_statement> st (
      odb::details::inc_ref (
        static_cast<select_statement*> (pq.stmt.get ())));

    mysql::connection& conn (
      mysql::transaction::current ().connection ());

    // The connection used by the current transaction and the
    // one used to prepare this statement must be the same.
    //
    assert (&conn == &st->connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    pq.query.init_parameters ();
    st->execute ();

    return shared_ptr<result_impl> (
      new (shared) mysql::object_result_impl<object_type> (
        pq.query, st, sts));
  }
}

#include <odb/post.hxx>