#include "Function/Input/InputSystem.h"  
#include "Core/Window/WindowSystem.h"  
#include "Function/Global/GlobalContext.h"  
#include <memory>  

namespace Taurus  
{  
   std::set<KeyCode> InputSystem::m_Keys;  

   InputSystem::InputSystem()  
   {  
       std::shared_ptr<WindowSystem> window_system = g_runtime_global_context.m_window_system;

       window_system->registerOnKeyFunc(std::bind(&InputSystem::OnKey, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
   }  

   bool InputSystem::IsKeyPressed(const KeyCode key)  
   {  
       return m_Keys.find(key) != m_Keys.end();  
   }

   void InputSystem::OnKey(int key, int scancode, int action, int mods)
   {
       if (action == 1)
       {
           m_Keys.insert(key);
       }
       else if (action == 0)
       {
           m_Keys.erase(key);
       }
   }
}