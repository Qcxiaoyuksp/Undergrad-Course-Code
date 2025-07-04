package 课设;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextArea;
import java.awt.Font;
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
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import java.awt.Choice;
import java.awt.Color;

public class Find extends JFrame {
	private JPanel contentPane;
	private JTextField textField;
	private JTextField txtInputDown;
	/**
	 *启动应用程序
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Find frame = new Find();
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
	public Find() {
		setTitle("Find");
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
		JTextArea txtrYouWant = new JTextArea();
		txtrYouWant.setBounds(15,10,200,20);
		txtrYouWant.setEditable(false);
		txtrYouWant.setBackground(SystemColor.menu);
		txtrYouWant.setFont(new Font("宋体",Font.PLAIN,16));
		txtrYouWant.setText("What do you want to find\uFF1A");
		contentPane.add(txtrYouWant);
		Choice choice = new Choice();
		choice.setBounds(250,10,150,25);
		choice.setFont(new Font("宋体",Font.PLAIN,16));
		choice.add("productID");
		choice.add("productName");
		choice.add("productAveragePrice");
		contentPane.add(choice);
		JList list = new JList();
		list.setBounds(0,0,1,1);
		contentPane.add(list);
		JTextArea txtrInput = new JTextArea();
		txtrInput.setBounds(15,40,400,20);
		txtrInput.setEditable(false);
		txtrInput.setBackground(SystemColor.menu);
		txtrInput.setFont(new Font("宋体",Font.PLAIN,16));
		txtrInput.setText("Please input product's ID or Name or AveragePrice\uFF1A");
		contentPane.add(txtrInput);
		textField = new JTextField();
		textField.setBounds(15,65,400,25);
		contentPane.add(textField);
		textField.setColumns(10);
		JTextArea txtrresult = new JTextArea();
		txtrresult.setBounds(15,110,95,20);
		txtrresult.setFont(new Font("宋体",Font.PLAIN,16));
		txtrresult.setBackground(SystemColor.menu);
		txtrresult.setEditable(false);
		txtrresult.setText("find result:");
		contentPane.add(txtrresult);
		JScrollPane scrollPane = new JScrollPane(list);
		scrollPane.setBounds(15,130,400,110);
		contentPane.add(scrollPane);
		/**
		 *设置查询按钮
		 */
		JButton btnSearch = new JButton("Find");
		btnSearch.setBounds(165,95,100,20);
		btnSearch.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Connection con;
		        Statement stat; 
		        ResultSet rs;
		        try {
		        	Class.forName("org.sqlite.JDBC");//加载驱动类
		        }
		        catch(Exception e1){
		        	java.lang.System.out.println(e1);
		        }
		        try{   
		        	con = DriverManager.getConnection("jdbc:sqlite://d:/javakeshe/digital products.s3db");//创建数据库连接
		        	stat=con.createStatement();
		        	//将输入信息在数据库中进行查找并打印相关信息
		            rs=stat.executeQuery("select * from digitalProducts where "+ choice.getSelectedItem()+" like '%%"+textField.getText()+"%%'");
		            if(choice.getSelectedItem()=="productID") {
		            	DefaultListModel productName=new DefaultListModel();
		            	while(rs.next()){
		            		productName.add(0, rs.getString(2));
			            	list.setModel(productName);
		            	}
		            }
		            else if(choice.getSelectedItem()=="productName") {
		            	DefaultListModel productID=new DefaultListModel();
		            	while(rs.next()){
		            		productID.add(0, rs.getString(1));
		            		list.setModel(productID);	
		            	}
		            }
		            else if(choice.getSelectedItem()=="productAveragePrice") {
		                DefaultListModel productName=new DefaultListModel();
		                while(rs.next()){
		                	productName.add(0, rs.getString(2));
		            	    list.setModel(productName);
		                }
		            }
		            con.close();
		        }
		        catch(SQLException e1){
		        	java.lang.System.out.println(e1);
		        }
			}
		});
		contentPane.add(btnSearch);
	}
}