package books.dao;
/*
 * 用户数据连接
 * sql操作
 * */
import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.BeanProcessor;
import org.apache.commons.dbutils.GenerousBeanProcessor;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.RowProcessor;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;
import org.junit.Test;

import books.entity.UserDB;
import books.utils.PageTool;
//import com.sxt.entity.UserDB;
import books.utils.sqlTools;

public class UserDao {
	QueryRunner queryRunner = new QueryRunner(sqlTools.getDataSource());
	
	//开启驼峰自动转换,（因为命名是驼峰，queryRunner查询数据库可能会有问题）
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	
	//删除user
	//@Test
	public int delUser(Integer uid) {
		String sql = "delete from t_user where uid = ?";
		Object[] params = {uid};
		try {
			
			return queryRunner.update(sql, params);
			
		} catch (SQLException e) {
			e.printStackTrace();
			System.out.println("111");
		}
		return -1; //删除失败
	}
	
	//用户列表
	/*
	public List<UserDB> list()
	{
		String sql="select * from t_user";
		try {
			return queryRunner.query(sql, new BeanListHandler<UserDB>(UserDB.class,processor));
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}*/
	
	
	
	/*
	 * 用户登录
	 * */
	//@Test
	public UserDB login(String account,String password)
	{
		String sql="select * from t_user where account =? and password=?"; //?为占位符
		Object[] params = {account,password};
		try {
			//UserDB 是用户实体类在books.entity
			 return queryRunner.query(sql, new BeanHandler<UserDB>(UserDB.class,processor),params);
			 //查询到该用户信息，返回
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	
	
	
	
	/**
	 * 用户列表 分页
	 * @return
	 */
	public PageTool<UserDB> list(String currentPage, String pageSize, Integer order){
		try {
			StringBuffer listSql = new StringBuffer("select * ");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer("from t_user");
			/*if (order != null && order == 1) {
				sql.append(" where role = 1 order by times desc");
			}*/
			//获取总记录数
			Long total = queryRunner.query(countSql.append(sql).toString(), new ScalarHandler<Long>());
			//初始化分页工具
			PageTool<UserDB> pageTools = new PageTool<UserDB>(total.intValue(), currentPage, pageSize);
			sql.append(" limit ?,?");
			//当前页的数据		
			 List<UserDB> list = queryRunner.query(listSql.append(sql).toString(), new BeanListHandler<UserDB>(UserDB.class, processor),pageTools.getStartIndex(),pageTools.getPageSize());
			 pageTools.setRows(list);
			 System.out.println(pageTools);
			 return pageTools;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return new PageTool<UserDB>(0, currentPage, pageSize);
	}
	
	 
	/**
	 * 添加用户
	 * @param userDB
	 * @return
	 */
	public Integer addUser(UserDB userDB) {
		String sql = "insert into t_user (account,password,name,phone,times,lend_num,max_num,role) values (?,?,?,?,?,?,?,?)";
		Object[] params = {userDB.getAccount(),userDB.getPassword(),userDB.getName(),userDB.getPhone(),userDB.getTimes(),userDB.getLendNum(),userDB.getMaxNum(),userDB.getRole()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	public List<UserDB> getList(UserDB userDB){
		String sql = "select * from t_user where account = ?";
		Object[] params = {userDB.getAccount()};
		try {
			return queryRunner.query(sql, new BeanListHandler<UserDB>(UserDB.class, processor),params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	/**
	 * 管理员修改用户信息
	 * @param userDB
	 * @return
	 */
	public Integer updUser(UserDB userDB) {
		String sql = "update t_user set phone = ?, lend_num = ?, max_num = ? where uid = ?";
		Object[] params = {userDB.getPhone(),userDB.getLendNum(),userDB.getMaxNum(),userDB.getUid()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 改变图书借阅信息
	 * @param userDB
	 * @return
	 * @throws SQLException
	 */
	public Integer updNum(UserDB userDB, Connection conn) throws SQLException {
		QueryRunner qr = new QueryRunner();
		String sql = "update t_user set times = ?, max_num = ? where uid = ?";
		Object[] params = {userDB.getTimes(),userDB.getMaxNum(),userDB.getUid()};
		return qr.update(conn, sql, params);
	}

}
					


