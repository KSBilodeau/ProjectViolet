//
//  debugComponents.hpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/14/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

// These objects are defined in a separate file in order to avoid a circular
// dependency between application.hpp and debugManager.hpp

#ifndef debugComponents_hpp
#define debugComponents_hpp

#ifndef DEBUG
#define ON_DEBUG(x) do { } while (0);
#else
#define ON_DEBUG(x) do { x } while (0);
#endif

enum MessageSeverity
{
    Information,
    Warning,
    SevereWarning,
    Error,
    SevereError,
    IrrecoverableError
};

#endif /* debugComponents_hpp */
