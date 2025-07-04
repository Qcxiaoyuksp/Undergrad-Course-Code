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


import com.dao.JiangzuoyuyueDao;
import com.entity.JiangzuoyuyueEntity;
import com.service.JiangzuoyuyueService;
import com.entity.vo.JiangzuoyuyueVO;
import com.entity.view.JiangzuoyuyueView;

@Service("jiangzuoyuyueService")
public class JiangzuoyuyueServiceImpl extends ServiceImpl<JiangzuoyuyueDao, JiangzuoyuyueEntity> implements JiangzuoyuyueService {


    @Override
    public PageUtils queryPage(Map<String, Object> params) {
        Page<JiangzuoyuyueEntity> page = this.selectPage(
                new Query<JiangzuoyuyueEntity>(params).getPage(),
                new EntityWrapper<JiangzuoyuyueEntity>()
        );
        return new PageUtils(page);
    }
    
    @Override
	public PageUtils queryPage(Map<String, Object> params, Wrapper<JiangzuoyuyueEntity> wrapper) {
		  Page<JiangzuoyuyueView> page =new Query<JiangzuoyuyueView>(params).getPage();
	        page.setRecords(baseMapper.selectListView(page,wrapper));
	    	PageUtils pageUtil = new PageUtils(page);
	    	return pageUtil;
 	}
    
    @Override
	public List<JiangzuoyuyueVO> selectListVO(Wrapper<JiangzuoyuyueEntity> wrapper) {
 		return baseMapper.selectListVO(wrapper);
	}
	
	@Override
	public JiangzuoyuyueVO selectVO(Wrapper<JiangzuoyuyueEntity> wrapper) {
 		return baseMapper.selectVO(wrapper);
	}
	
	@Override
	public List<JiangzuoyuyueView> selectListView(Wrapper<JiangzuoyuyueEntity> wrapper) {
		return baseMapper.selectListView(wrapper);
	}

	@Override
	public JiangzuoyuyueView selectView(Wrapper<JiangzuoyuyueEntity> wrapper) {
		return baseMapper.selectView(wrapper);
	}

    @Override
    public List<Map<String, Object>> selectValue(Map<String, Object> params, Wrapper<JiangzuoyuyueEntity> wrapper) {
        return baseMapper.selectValue(params, wrapper);
    }

    @Override
    public List<Map<String, Object>> selectTimeStatValue(Map<String, Object> params, Wrapper<JiangzuoyuyueEntity> wrapper) {
        return baseMapper.selectTimeStatValue(params, wrapper);
    }
    
    @Override
    public List<Map<String, Object>> selectGroup(Map<String, Object> params, Wrapper<JiangzuoyuyueEntity> wrapper) {
        return baseMapper.selectGroup(params, wrapper);
    }

}
