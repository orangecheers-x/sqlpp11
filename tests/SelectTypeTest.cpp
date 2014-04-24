/*
 * Copyright (c) 2013-2014, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include "Sample.h"
#include "MockDb.h"
#include "is_regular.h"
#include <sqlpp11/alias_provider.h>
#include <sqlpp11/select.h>
#include <sqlpp11/functions.h>
#include <sqlpp11/connection.h>


MockDb db = {};
MockDb::_serializer_context_t printer;

namespace alias
{
	SQLPP_ALIAS_PROVIDER(a);
	SQLPP_ALIAS_PROVIDER(b);
	SQLPP_ALIAS_PROVIDER(left);
	SQLPP_ALIAS_PROVIDER(right);
}

int main()
{
	test::TabFoo f; 
	test::TabBar t;

	// Test a table
	{
		using T = decltype(t);
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an alias of table
	{
		using T = decltype(t.as(alias::a));
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an integral column of an alias of table
	{
		using T = decltype(t.as(alias::a).alpha);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}


	// Test an integral table column
	{
		using T = decltype(t.alpha);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a floating point table column
	{
		using T = decltype(f.omega);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_integral_t<T>::value, "type requirement");
		static_assert(sqlpp::is_floating_point_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a an alias of a numeric table column
	{
		using T = decltype(t.alpha.as(alias::a));
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a select of a single column without a from
	{
		using T = decltype(select(t.alpha)); // Hint: The current rule is pretty crude (a from is required), but certainly better than nothing
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a select of a single numeric table column
	{
		using T = decltype(select(t.alpha).from(t));
		static_assert(sqlpp::is_select_column_list_t<decltype(T::_column_list)>::value, "Must not be noop");
		static_assert(sqlpp::is_from_t<decltype(T::_from)>::value, "Must not be noop");
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test a select of an alias of a single numeric table column
	{
		using T = decltype(select(t.alpha.as(alias::a)).from(t));
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an alias of a select of a single numeric table column
	{
		using T = decltype(select(t.alpha).from(t).as(alias::b));
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "red to not be boolean");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test the column of an alias of a select of an alias of a single numeric table column
	{
		using T = decltype(select(t.alpha.as(alias::a)).from(t).as(alias::b));
		static_assert(not sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(not sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test the column of an alias of a select of a single numeric table column
	{
		using T = decltype(select(t.alpha).from(t).as(alias::b).alpha);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test an alias of a select of an alias of a single numeric table column
	{
		using T = decltype(select(t.alpha.as(alias::a)).from(t).as(alias::b).a);
		static_assert(sqlpp::is_numeric_t<T>::value, "type requirement");
		static_assert(sqlpp::is_expression_t<T>::value, "type requirement");
		static_assert(sqlpp::is_named_expression_t<T>::value, "type requirement");
		static_assert(not sqlpp::require_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_insert_t<T>::value, "type requirement");
		static_assert(sqlpp::must_not_update_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_boolean_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_text_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_alias_t<T>::value, "type requirement");
		static_assert(not sqlpp::is_table_t<T>::value, "type requirement");
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test that select(all_of(tab)) is expanded in select
	{
		auto a = select(all_of(t));
		auto b = select(t.alpha, t.beta, t.gamma, t.delta);
		//auto c = select(t);
		static_assert(std::is_same<decltype(a), decltype(b)>::value, "all_of(t) has to be expanded by select()");
		//static_assert(std::is_same<decltype(b), decltype(c)>::value, "t has to be expanded by select()");
	}

	// Test that select(all_of(tab)) is expanded in multi_column
	{
		auto a = multi_column(all_of(t)).as(alias::a);
		auto b = multi_column(t.alpha, t.beta, t.gamma, t.delta).as(alias::a);
		static_assert(std::is_same<decltype(a), decltype(b)>::value, "all_of(t) has to be expanded by multi_column");
	}

	// Test that a multicolumn is not a value
	{
		auto m = multi_column(t.alpha, t.beta).as(alias::a);
		auto a = select(m).from(t).as(alias::b).a;
		static_assert(not sqlpp::is_value_t<decltype(a)>::value, "a multi_column is not a value");
	}
	// Test that result sets with identical name/value combinations have identical types
	{
		auto a = select(t.alpha);
		auto b = select(f.epsilon.as(t.alpha));
		using A = typename decltype(a)::_result_row_t<MockDb>;
		using B = typename decltype(b)::_result_row_t<MockDb>;
		static_assert(std::is_same<
				decltype(t.alpha)::_value_type::_base_value_type, 
				decltype(f.epsilon)::_value_type::_base_value_type>::value, "Two bigint columns must have identical base_value_type");
		static_assert(std::is_same<A, B>::value, "select with identical columns(name/value_type) need to have identical result_types");
	}

	for (const auto& row : db(select(all_of(t)).from(t).where(true)))
	{
		int64_t a = row.alpha;
	}

	{
		auto s = dynamic_select(db, all_of(t)).dynamic_from().dynamic_where().dynamic_limit().dynamic_offset();
		s.add_from(t);
		s.add_where(t.alpha > 7 and t.alpha == any(select(t.alpha).from(t).where(t.alpha < 3)));
		s.set_limit(30);
		s.set_limit(3);
		std::cerr << "------------------------\n";
		serialize(s, printer).str();
		std::cerr << "------------------------\n";
		using T = decltype(s);
		static_assert(sqlpp::is_regular<T>::value, "type requirement");
	}

	// Test that select can be called with zero columns if it is used with dynamic columns.
	{
		auto s = dynamic_select(db).dynamic_columns().extra_tables(t);
		s.add_column(t.alpha);
		serialize(s, printer).str();
	}

	// Test that verbatim_table compiles
	{
		auto s = select(t.alpha).from(sqlpp::verbatim_table("my_unknown_table"));
		serialize(s, printer).str();
	}


	static_assert(sqlpp::is_select_flag_t<decltype(sqlpp::all)>::value, "sqlpp::all has to be a select_flag");
  using T = sqlpp::vendor::wrap_operand<int>::type;
	static_assert(sqlpp::is_regular<T>::value, "type requirement");
	static_assert(T::_is_expression, "T has to be an expression");
	static_assert(std::is_same<typename T::_value_type::_is_numeric, std::true_type>::value, "T has to be a numeric");
	static_assert(sqlpp::is_numeric_t<T>::value, "T has to be a numeric");
	static_assert(sqlpp::is_numeric_t<decltype(t.alpha)>::value, "TabBar.alpha has to be a numeric");
	((t.alpha + 7) + 4).asc();
	static_assert(sqlpp::is_boolean_t<decltype(t.gamma == t.gamma)>::value, "Comparison expression have to be boolean");
	auto x = (t.gamma == true) and (t.alpha == 7);
	auto y = t.gamma and true and t.gamma;
	!t.gamma;
	t.beta < "kaesekuchen";
	serialize(t.beta + "hallenhalma", printer).str();
	static_assert(sqlpp::must_not_insert_t<decltype(t.alpha)>::value, "alpha must not be inserted");
	serialize(t.alpha, printer).str();
	std::cerr << "\n" << sizeof(test::TabBar) << std::endl;
	static_assert(std::is_same<typename decltype(t.alpha)::_value_type::_is_named_expression, std::true_type>::value, "alpha should be a named expression");
	static_assert(sqlpp::is_named_expression_t<decltype(t.alpha)>::value, "alpha should be a named expression");
	static_assert(sqlpp::is_named_expression_t<decltype(t.alpha.as(alias::a))>::value, "an alias of alpha should be a named expression");
	static_assert(sqlpp::is_alias_t<decltype(t.alpha.as(alias::a))>::value, "an alias of alpha should be an alias");

	auto z = select(t.alpha).from(t) == 7;
	auto l = t.as(alias::left);
	auto r = select(t.gamma.as(alias::a)).from(t).where(t.gamma == true).as(alias::right);
	using R = decltype(r);
	static_assert(sqlpp::is_boolean_t<decltype(select(t.gamma).from(t))>::value, "select(bool) has to be a bool");
	auto s = select(r.a).from(r);
	using RA = decltype(r.a);
	using S = decltype(s);
	using SCL = typename S::_column_list_t;
	using SF = typename S::_from_t;
	static_assert(sqlpp::is_select_column_list_t<SCL>::value, "no column list");
	static_assert(sqlpp::is_from_t<SF>::value, "no from list");
	using SCL_T = typename SCL::_table_set;
	using SF_T = typename SF::_table_set;
	static_assert(SCL_T::size::value == 1, "unexpected table_set in column_list");
	static_assert(SF_T::size::value == 1, "unexpected table_set in from");
	static_assert(std::is_same<SCL_T, SF_T>::value, "should be the same");
	static_assert(sqlpp::is_boolean_t<decltype(select(r.a).from(r))>::value, "select(bool) has to be a bool");
	auto s1 = sqlpp::select().flags(sqlpp::distinct, sqlpp::straight_join).columns(l.alpha, l.beta, select(r.a).from(r))
		.from(r,t,l)
		.where(t.beta == "hello world" and select(t.gamma).from(t))// .as(alias::right))
		.group_by(l.gamma, r.a)
		.having(r.a != true)
		.order_by(l.beta.asc())
		.limit(17)
		.offset(3)
		.as(alias::a)
		;


	return 0;
}
