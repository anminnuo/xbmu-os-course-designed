package database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectDatabase {

	public static Connection connectDB() {

		String url = "jdbc:mysql:// localhost:3308/mis";//?serverTimezone=GMT%2B8

		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		} catch (Exception e) {
		}

		Connection con = null;

		try {
			con = DriverManager.getConnection(url, "root", "root");
		} catch (SQLException e) {
		}

		return con;
	}
}
