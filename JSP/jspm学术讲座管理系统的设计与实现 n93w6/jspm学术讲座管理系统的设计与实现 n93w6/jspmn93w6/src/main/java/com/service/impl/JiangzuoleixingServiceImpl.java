package com.service.impl;

import org.springframework.stereotype.Service;
import java.util.Map;
import java.util.List;

import com.baomidou.mybatisplus.mapper.Wrapper;
import com.baomidou.mybatisplus.mapper.EntityWrapper;
import com.baomidou.mybatisplus.plugins.Page;
import com.baomidou.mybatisplus.service.impl.ServiceImpl;
import com.utils.PageUtils;
import com.utils.Query;


import com.dao.JiangzuoleixingDao;
import com.entity.JiangzuoleixingEntity;
import com.service.JiangzuoleixingService;
import com.entity.vo.JiangzuoleixingVO;
import com.entity.view.JiangzuoleixingView;

@Service("jiangzuoleixingService")
public class JiangzuoleixingServiceImpl extends ServiceImpl<JiangzuoleixingDao, JiangzuoleixingEntity> implements JiangzuoleixingService {


    @Override
    public PageUtils queryPage(Map<String, Object> params) {
        Page<JiangzuoleixingEntity> page = this.selectPage(
                new Query<JiangzuoleixingEntity>(params).getPage(),
                new EntityWrapper<JiangzuoleixingEntity>()
        );
        return new PageUtils(page);
    }
    
    @Override
	public PageUtils queryPage(Map<String, Object> params, Wrapper<JiangzuoleixingEntity> wrapper) {
		  Page<JiangzuoleixingView> page =new Query<JiangzuoleixingView>(params).getPage();
	        page.setRecords(baseMapper.selectListView(page,wrapper));
	    	PageUtils pageUtil = new PageUtils(page);
	    	return pageUtil;
 	}
    
    @Override
	public List<JiangzuoleixingVO> selectListVO(Wrapper<JiangzuoleixingEntity> wrapper) {
 		return baseMapper.selectListVO(wrapper);
	}
	
	@Override
	public JiangzuoleixingVO selectVO(Wrapper<JiangzuoleixingEntity> wrapper) {
 		return baseMapper.selectVO(wrapper);
	}
	
	@Override
	public List<JiangzuoleixingView> selectListView(Wrapper<JiangzuoleixingEntity> wrapper) {
		return baseMapper.selectListView(wrapper);
	}

	@Override
	public JiangzuoleixingView selectView(Wrapper<JiangzuoleixingEntity> wrapper) {
		return baseMapper.selectView(wrapper);
	}


}
