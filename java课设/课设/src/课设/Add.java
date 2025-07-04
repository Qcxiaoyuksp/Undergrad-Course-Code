package 课设;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextArea;
import java.awt.SystemColor;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.awt.Color;

public class Add extends JFrame {
	private JPanel contentPane;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	/**
	 *启动应用程序
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Add frame = new Add();
					frame.setVisible(true);
				} 
				catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	/**
	 *建立框架
	 */
	public Add() {
		setTitle("Add");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(750,350,450,300);//界面大小
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);//面板背景着色
		contentPane.setBorder(new EmptyBorder(5,5,5,5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		/**
		 *界面布局
		 */
		JTextArea txtrTeam = new JTextArea();
		txtrTeam.setBounds(50,27,125,20);
		txtrTeam.setEditable(false);
		txtrTeam.setBackground(SystemColor.menu);
		txtrTeam.setText("             productID         \uFF1A");
		contentPane.add(txtrTeam);//产品排名
		JTextArea txtrPlayerName = new JTextArea();
		txtrPlayerName.setBounds(50,62,125,20);
		txtrPlayerName.setBackground(SystemColor.menu);
		txtrPlayerName.setText("         productName     \uFF1A");
		contentPane.add(txtrPlayerName);//产品名称
		JTextArea txtrUniformNumber = new JTextArea();
		txtrUniformNumber.setBounds(50,97,125,20);
		txtrUniformNumber.setText(" productAveragePrice \uFF1A");
		txtrUniformNumber.setBackground(SystemColor.menu);
		contentPane.add(txtrUniformNumber);//产品均价
		JTextArea txtrPlayerPrice = new JTextArea();
		txtrPlayerPrice.setBounds(50,132,125,20);
		txtrPlayerPrice.setText("          productScore     \uFF1A");
		txtrPlayerPrice.setBackground(SystemColor.menu);
		contentPane.add(txtrPlayerPrice);//产品评分
		textField = new JTextField();
		textField.setBounds(175,25,200,25);
		contentPane.add(textField);//产品排名的输入栏
		textField.setColumns(10);
		textField_1 = new JTextField();
		textField_1.setBounds(175,60,200,25);//产品名称的输入栏
		textField_1.setColumns(10);
		contentPane.add(textField_1);
		textField_2 = new JTextField();
		textField_2.setBounds(175,95,200,25);//产品均价的输入栏
		textField_2.setColumns(10);
		contentPane.add(textField_2);
		textField_3 = new JTextField();
		textField_3.setBounds(175,130,200,25);//产品评分的输入栏
		textField_3.setColumns(10);
		contentPane.add(textField_3);
		/**
		 *设置确认按钮
		 */
		JButton btnConfirm = new JButton("Confirm");
		btnConfirm.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				 Connection con;
		         Statement stat; 
		         ResultSet rs;
		         try {  
		        	 Class.forName("org.sqlite.JDBC");//加载驱动类   
		         }
		         catch(Exception e){
		               java.lang.System.out.println(""+e);
		         }
		         try {
		        	   con=DriverManager.getConnection("jdbc:sqlite://d:/javakeshe/digital products.s3db");//创建数据库连接
		               stat=con.createStatement();
		               //将输入信息嵌入数据库
		               String s="insert into digitalProducts values('"+textField.getText()+"','"+textField_1.getText()+"','"+textField_2.getText()+"','"+textField_3.getText()+"')";
		               int count=stat.executeUpdate(s);
		               if(count==1)
		            	   java.lang.System.out.println("Add succeeded!");
		               else
		            	   java.lang.System.out.println("Add false!");
		               rs=stat.executeQuery("select * from digitalProducts");//查询数据库中的信息
		               //打印数据库中信息
		               while(rs.next()){
		                  int productID=rs.getInt(1);
		                  String productName=rs.getString(2);
		                  float productAveragePrice=rs.getFloat(3);
		                  float productScore=rs.getFloat(4);
		                  java.lang.System.out.println(productID+","+productName+","+productAveragePrice+","+productScore);
		               }
		               con.close();
		         }
		         catch(SQLException e){
		        	 java.lang.System.out.println(e);
		         }
			}
		});
		btnConfirm.setBounds(140,190,150,30);
		contentPane.add(btnConfirm);	
	}
}