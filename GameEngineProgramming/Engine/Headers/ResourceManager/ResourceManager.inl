
template <typename T>
inline T * ResourceManager::GetResource( const std::string & resourceTag )
{
	//	TODO: Type check
	return dynamic_cast<T *>( m_ResourceMap[resourceTag] );
}
