package books.utils;

//c3p0工具类
/*
 * C3P0是一JDBC连接池，它实现了数据源和JNDI绑定，
 * 支持JDBC3规范和JDBC2的标准扩展。
 * */
import java.sql.Connection;
import java.sql.SQLException;

import javax.sql.DataSource;

import com.mchange.v2.c3p0.ComboPooledDataSource;


public class sqlTools {
	
	private static DataSource dataSource = new ComboPooledDataSource();
	
	/**
	 * 获取数据源
	 * @return
	 */
	public static DataSource getDataSource() {
		return dataSource;
	}
	
	/**
	 * 获取连接
	 * @return
	 */
	public static Connection getConnection() {
		try {
			return dataSource.getConnection();
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException();
		}
	}

}
