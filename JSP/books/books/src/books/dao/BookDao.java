package books.dao;

import java.sql.Connection;
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

import books.entity.BookDB;
import books.utils.sqlTools;
import books.utils.PageTool;

public class BookDao {

	QueryRunner queryRunner = new QueryRunner(sqlTools.getDataSource());
	//开启驼峰自动转换
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	/**
	 * 图书列表 分页
	 * @return
	 */
	public PageTool<BookDB> list(String currentPage, String pageSize, String word, Integer order){
		try {
			StringBuffer listSql = new StringBuffer("select b.*,type_name ");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer("from t_book b LEFT JOIN t_type t ON b.tid = t.tid");
			if (word != null && !word.isEmpty()) {  //模糊查询
				sql.append(" where book_name like '%" + word + "%'");
				sql.append(" or type_name like '%" + word + "%'");
				sql.append(" or author like '%" + word + "%'");
				sql.append(" or press like '%" + word + "%'");
			}
			if (order != null && order == 1) {
				sql.append(" order by times desc");
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
	 * @return
	 */
	public List<BookDB> list(String bookName, String bid){
		StringBuffer sql = new StringBuffer("select * from t_book where 1 = 1 ");
		List<Object> params = new ArrayList<>();
		if (bookName != null && bookName != "") {
			sql.append("and book_name = ? ");
			params.add(bookName);
		}
		if (bid != null && bid != "") {
			sql.append("and bid = ?");
			params.add(bid);
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
	 * @param BookDB
	 * @return
	 */
	public Integer addBook(BookDB bookDB) {
		String sql = "insert into t_book (book_name,author,num,press,tid,times) values (?,?,?,?,?,0)";
		Object[] params = {bookDB.getBookName(),bookDB.getAuthor(),bookDB.getNum(),bookDB.getPress(),bookDB.getTid()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 修改图书信息
	 * @return
	 */
	public Integer updBook(BookDB bookDB) {
		String sql = "update t_book set tid = ?, press = ?, num = ? where bid = ?";
		Object[] params = {bookDB.getTid(),bookDB.getPress(),bookDB.getNum(),bookDB.getBid()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 改变库存
	 * @param bookDB
	 * @return
	 * @throws SQLException 
	 */
	public Integer changeNum(BookDB bookDB, Connection conn) throws SQLException {
		QueryRunner qr = new QueryRunner();
		String sql = "update t_book set times = ? ,num = ? where bid = ?";
		Object[] params = {bookDB.getTimes(),bookDB.getNum(),bookDB.getBid()};
		return qr.update(conn, sql, params);
	}
	
	/**
	 * 删除图书
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
