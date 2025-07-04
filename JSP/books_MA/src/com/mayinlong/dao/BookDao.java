package com.mayinlong.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.BeanProcessor;
import org.apache.commons.dbutils.GenerousBeanProcessor;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.RowProcessor;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;

import com.mayinlong.entity.BookDB;
import com.mayinlong.utils.C3p0Tool;
import com.mayinlong.utils.PageTool;

public class BookDao {
	QueryRunner queryRunner = new QueryRunner(C3p0Tool.getDataSource());
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	
	public PageTool<BookDB> list(String currentPage, String pageSize,String word){
		try {
			StringBuffer listSql = new StringBuffer("select b.*,type_name ");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer("from t_book b LEFT JOIN t_type t ON b.tid = t.tid");
			if (word != null && !word.isEmpty()) {
				sql.append(" where book_name like '%" + word + "%'");
				sql.append(" or type_name like '%" + word + "%'");
				sql.append(" or author like '%" + word + "%'");
				sql.append(" or press like '%" + word + "%'");
				sql.append(" or press like '%" + word + "%'");
				sql.append(" or part like '%" + word + "%'");
				sql.append(" or digest like '%" + word + "%'");
				sql.append(" or code like '%" + word + "%'");
				sql.append(" or grade like '%" + word + "%'");
				sql.append(" or shoulu like '%" + word + "%'");
				sql.append(" or project like '%" + word + "%'");
			}
			//获取总记录数
			Long total = queryRunner.query(countSql.append(sql).toString(), new ScalarHandler<Long>());
			//初始化分页工具
			PageTool<BookDB> pageTools = new PageTool<BookDB>(total.intValue(), currentPage, pageSize);
			sql.append(" limit ?,?");
			//当前页的数据		
			 List<BookDB> list = queryRunner.query(listSql.append(sql).toString(), new BeanListHandler<BookDB>(BookDB.class, processor),pageTools.getStartIndex(),pageTools.getPageSize());
			 pageTools.setRows(list);
			 System.out.println(pageTools);
			 return pageTools;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return new PageTool<BookDB>(0, currentPage, pageSize);
	}
	
	/**
	 * 多条件查询
	 * @param tid
	 * @param typeName
	 * @return
	 */
	public List<BookDB> list(String bookName){
		StringBuffer sql = new StringBuffer("select * from t_book where 1 = 1 ");
		List<Object> params = new ArrayList<>();
		if (bookName != null && bookName != "") {
			sql.append("and book_name = ?");
			params.add(bookName);
		}
		try {
			return queryRunner.query(sql.toString(), new BeanListHandler<BookDB>(BookDB.class, processor), params.toArray());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 添加图书
	 * @param 
	 * @return
	 */
	public Integer addBook(BookDB bookDB) {
		String sql = "insert into t_book (book_name,author,num,press,tid,times,part,digest,code,grade,shoulu,project) values (?,?,?,?,?,0,?,?,?,?,?,?)";
		Object[] params = {bookDB.getbookName(),bookDB.getAuthor(),bookDB.getNum(),bookDB.getPress(),bookDB.getTid(),bookDB.getPart(),bookDB.getDigest(),bookDB.getCode(),bookDB.getGrade(),bookDB.getShoulu(),bookDB.getProject()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 修改论文信息
	 * @return
	 */
	public Integer updBook(BookDB bookDB) {
		String sql = "update t_book set tid = ?, press = ?, num = ?, part= ? , digest = ?, code = ?, grade = ?, shoulu= ?, project = ?where bid = ?";
		Object[] params = {bookDB.getTid(),bookDB.getPress(),bookDB.getNum(),bookDB.getBid(),bookDB.getPart(),bookDB.getDigest(),bookDB.getCode(),bookDB.getGrade(),bookDB.getShoulu(),bookDB.getProject()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 删除论文
	 * @return 
	 */
	public int delBook(String bid) {
		String sql = "delete from t_book where bid = ?";
		Object[] params = {bid};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return -1;
	}
	
	
}
